#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "tables.h"

static bool a_instruction(char *buffer, char *instruction, symbol *symboltable);
static bool c_instruction(char *buffer, char *instruction, symbol *symboltable);

bool assemble(char *buffer, char *instruction, symbol *symboltable) {
    bool is_a, return_val;
    instruction[0] == '@' ? is_a = true : is_a = false;

    if (is_a)
        return_val = a_instruction(buffer, instruction, symboltable);
    else
        return_val = c_instruction(buffer, instruction, symboltable);

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

    if (isdigit((unsigned char)fuekd[0])) {
        is_symbol = false;
        value = atoi(field);
        if (value == 0)
            return false;
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

    //translate value

}

static bool c_instruction(char *buffer, char *instruction, symbol *symboltable) {
    buffer[0] = '1';
    buffer[1] = '1';
    buffer[2] = '1';

}
