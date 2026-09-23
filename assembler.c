#include <stdbool.h>
#include "tables.h"

bool assemble(char *buffer, char *instruction, symbol *symboltable) {
    bool is_a, return_val;
    if (instruction[0] == '@')
        is_a = true;

    if (is_a)
        a_instruction();
    else
        c_instruction();

    return return_val;
}

static bool a_instruction() {

}

static bool c_instruction() {

}
