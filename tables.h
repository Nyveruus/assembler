#ifndef TABLES_H
#define TABLES_H
#define MAX_SYMBOLS 1024

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
    char name[64]
    unsigned int value;
} symbol;

extern const fields table;

#endif
