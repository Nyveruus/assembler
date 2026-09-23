#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include "tables.h"
#include <stdbool.h>
bool assemble(char *buffer, char *instruction, symbol *symboltable);
#endif
