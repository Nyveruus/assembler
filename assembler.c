#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"

#define A_BITS 15

#define COMP_DELIM "="
#define JUMP_DELIM ";"

#define COMP_OFFSET 3
#define DEST_OFFSET 10
#define JUMP_OFFSET 13

#define NUMB_COMP 7
#define NUMB_DESTJUMP 3

static bool a_instruction(char *buffer, char *instruction, symbol *symboltable);
static bool c_instruction(char *buffer, char *instruction);
static const char *lookup_field(char *key, const entry *table);

bool assemble(char *buffer, char *instruction, symbol *symboltable) {
    bool is_a, return_val;
    instruction[0] == '@' ? is_a = true : (is_a = false);

    if (is_a)
        return_val = a_instruction(buffer, instruction, symboltable);
    else
        return_val = c_instruction(buffer, instruction);

    return return_val;
}

static bool a_instruction(char *buffer, char *instruction, symbol *symboltable) {

    buffer[0] = '0';

    /*
     * address or symbol. We need to check for two cases, if everything after @ is a number or if it's a symbol. If it's a symbol, look it up in table
     * if it is found, use value. If it is not found, add it to symbol table and use lookup to find value for translating
     *
     * In both cases we will translate decimal to symbolic binary but we need to know what to translate (every thing after @ or the symbol value)
     */

    char *field = instruction + 1;
    unsigned int value;
    bool is_symbol = true;

    if (isdigit((unsigned char)field[0])) {
        is_symbol = false;
        value = atoi(field);
    }

    if (is_symbol) {
        unsigned int table_value;
        if (symbolt_lookup(field, symboltable, &table_value)) {
            value = table_value;
        } else {
            symbolt_add(field, 0, symboltable, true);
            symbolt_lookup(field, symboltable, &table_value);
            value = table_value;
        }
    }

    /*
     * Convert decimal to binary representation in buffer. Instead of using convoluted logic maybe can try to take advantage of the fact that
     * the underlying bit positions of the int and the output for this part of the buffer are symbolically equivalent. Buffer[0] and buffer[16]
     * must not be touched, so this needs to be factored in as an offset and cut off point. Iterating forwards (1 to 15) is not possible (or ideal)
     * because it would cause the buffer bit order to be reversed (little endian) and would pad bits to the right instead of left, bad address.
     * Must iterate backwards (15 to 1). For each iteration find amount to bit shift
     */

    for (int i = A_BITS; i >= 1; i--) {

        int bit_shift = A_BITS - i;
        char bit;

        if ((1 << bit_shift) & value)
            bit = '1';
        else
            bit = '0';

        buffer[i] = bit;
    }

    return true;
}

/*
 * We will search for delimiters and set pointers to those addresses + 1, replace each delimiter with null terminator to effectively split into separate char strings
 * each with pointer. Missing delimiters could be handled by setting to "" by default to match to NULL in field table. jump and dest are optional so mostly work around comp.
 * Once pointers to each char string is obtained, look them up (look up return NULL on error) and print to buffer in order
 */

static bool c_instruction(char *buffer, char *instruction) {
    buffer[0] = '1';
    buffer[1] = '1';
    buffer[2] = '1';

    char *comp = instruction;
    char *dest = "";
    char *jump = "";

    char *tmp0 = strstr(instruction, COMP_DELIM);
    char *tmp1 = strstr(instruction, JUMP_DELIM);

    if (tmp0 != NULL) {
        comp = tmp0 + 1;
        *tmp0 = '\0';
        dest = instruction;
    }

    if (tmp1 != NULL) {
        jump = tmp1 + 1;
        *tmp1 = '\0';
    }

    const char *comp_return = lookup_field(comp, fieldtable.comp_table);
    const char *dest_return = lookup_field(dest, fieldtable.dest_table);
    const char *jump_return = lookup_field(jump, fieldtable.jump_table);

    if (!comp_return || !dest_return || !jump_return)
        return false;

    // use memcpy instead of strcpy because we cannot include null terminator for each field
    memcpy(buffer + COMP_OFFSET, comp_return, NUMB_COMP);
    memcpy(buffer + DEST_OFFSET, dest_return, NUMB_DESTJUMP);
    memcpy(buffer + JUMP_OFFSET, jump_return, NUMB_DESTJUMP);

    return true;
}

static const char *lookup_field(char *key, const entry *table) {
    for (const entry *ee = table; ee->name != NULL; ee++) {
        if (!strcmp(ee->name, key))
            return ee->number;
    }
    return NULL;
}
