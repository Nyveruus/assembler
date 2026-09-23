#ifndef TABLES_H
#define TABLES_H
#define MAX_SYMBOLS 1024
#define MAX_SYMLEN 64
#include <stdbool.h>

typedef struct {
    const char *name;
    const char *number;
} entry;

typedef struct {
    const entry *comp_table;
    const entry *dest_table;
    const entry *jump_table;
} fields;

typedef struct {
    char name[MAX_SYMLEN];
    unsigned int value;
} symbol;

extern const fields fieldtable;

int symbolt_init(symbol *symboltable);
int symbolt_add(char *name, size_t value, symbol *symboltable, bool isvar);
bool symbolt_lookup(char *name, symbol *symboltable, unsigned int return_value);

#endif
