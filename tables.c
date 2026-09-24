#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tables.h"
#define MAX_SYMLEN 64
#define NUM_REGS 16


int symbolt_add(char *name, size_t value, symbol *symboltable, bool isvar);

/* Better to just use global variables to avoid overcomplexity and nesting */
static const entry comp[] = {
    {"0", "0101010"}, {"1", "0111111"}, {"-1", "0111010"},
    {"D", "0001100"}, {"A", "0110000"}, {"!D", "0001101"},
    {"!A", "0110001"}, {"-D", "0001111"}, {"-A", "0110011"},
    {"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"},
    {"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
    {"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"},
    {"M", "1110000"}, {"!M", "1110001"}, {"-M", "1110011"},
    {"M+1", "1110111"}, {"M-1", "1110010"}, {"D+M", "1000010"},
    {"D-M", "1010011"}, {"M-D", "1000111"}, {"D&M", "1000000"},
    {"D|M", "1010101"}, {NULL, NULL}
};

static const entry dest[] = {
    {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"},
    {"A", "100"}, {"AM", "101"}, {"AD", "110"}, {"AMD", "111"},
    {NULL, NULL}
};

static const entry jump[] = {
    {"", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
    {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"},
    {NULL, NULL}
};

const fields fieldtable = {
    .comp_table = comp,
    .dest_table = dest,
    .jump_table = jump
};

static symbol predefined[] = {
    {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4},
    {"SCREEN", 16384}, {"KBD", 24576}
};

static size_t count = 0;
// hack vars must start at value 16
static size_t next_var = 16;

int symbolt_init(symbol *symboltable) {

    /*
     * Separate counter to track what indexes are used in table will have to be used to avoid overwritting
     * previously set symbols. Maybe the best approach is to use a universal adder function (for variables too)
     * with a static counter that can be used each time a new symbol is entered
     */

    for (size_t i = 0; i < sizeof(predefined)/sizeof(predefined[0]); i++) {
        symbolt_add(predefined[i].name, predefined[i].value, symboltable, false);
    }
    for (size_t i = 0; i < NUM_REGS; i++) {
        char name [4];
        snprintf(name, sizeof(name), "R%li", i);
        symbolt_add(name, i, symboltable, false);
    }
    return 0;
}

int symbolt_add(char *name, size_t value, symbol *symboltable, bool isvar) {

    /*
     * Indexes must never collide, values for predefined symbols can collide and for user set symbols,
     * value is the index, incrementing. I will need to track whether the symbol is predefined or user set
     * to know what value should be, count or symboltable value, use a simple bool entered in caller.
     * We only care about int value for predefined symbols, otherwise = count
     */

    if (count > MAX_SYMBOLS) {
        fprintf(stderr, "Max symbols exceeded\n");
        exit(1);
    }
    if (strlen(name) >= MAX_SYMLEN - 1) {
        fprintf(stderr, "Symbol size exceeded\n");
        exit(1);
    }

    strcpy(symboltable[count].name, name);

    //isvar ? symboltable[count].value = count : (symboltable[count].value = value);
    symboltable[count].value = isvar ? next_var++ : value;

    (void)value;
    count++;
    return 0;
}

bool symbolt_lookup(char *name, symbol *symboltable, unsigned int *return_value) {

    for (size_t i = 0; i < count; i++) {
        if (!strcmp(symboltable[i].name, name)) {
            *return_value = symboltable[i].value;
            return true;
        }
    }
    return false;
}
