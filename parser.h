#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
bool parser(char *linebuffer, char **line);
void first_pass_func(char *linebuffer, symbol *symboltable, size_t *instruction_count);

#endif
