#include <stdio.h>
#include "tables.h"

#define NUM_REGS 16

/* Better to just use global variables to avoid overcomplexity and nesting */
const static entry comp[] = {
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

const static entry dest[] = {
    {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"},
    {"A", "100"}, {"AM", "101"}, {"AD", "110"}, {"AMD", "111"},
    {NULL, NULL}
};

const static entry jump[] = {
    {"", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
    {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"},
    {NULL, NULL}
};

const fields optable = {
    .comp_table = comp,
    .dest_table = dest,
    .jump_table = jump
};

static const symbol predefined[] = {
    {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4},
    {"SCREEN", 16384}, {"KBD", 24576}
};

static size_t count = 0;

int symbolt_init(symbol *symboltable) {
    //predefined symbols and registers until 16

    /* Separate counter to track what indexes are used in table will have to be used to avoid overwritting
     * previously set symbols. Maybe the best approach is to use a universal adder function (for variables too)
     * with a static counter that can be used each time a new symbol is entered
     */

    for (int i = 0; i < sizeof(predefined)/sizeof(predefined[0]); i++) {
        symbolt_add(predefined[i].name, predefined[i].value);
    }
    for (int i = 0; i < NUM_REGS) {
        char name [4];
        snprintf(name, "R%i", i);
        symbolt_add(name, i);
    }
}
