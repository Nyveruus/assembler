#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "tables.h"

static bool preprocess(char *linebuffer, char **line);

bool parser(char *linebuffer, char **line) {
    if (!preprocess(linebuffer, line))
        return false;
    return true;
}

void first_pass_func(char *linebuffer, symbol *symboltable, size_t *instruction_count) {
    char *line;
    if (!preprocess(linebuffer, &line))
        return;

    // going forward we know line has chars either label or instruction

    if (*line != '(') {
        (*instruction_count)++;
        return;
    }

    char *start = strstr(line, "(");
    char *end = strstr(line, ")");
    start++;
    *end = '\0';

    symbolt_add(start, *instruction_count, symboltable, false);
}

static bool preprocess(char *linebuffer, char **line) {

    /*
     * Use a pointer for moving around the buffer, first check for any comments (//), set it to null terminator
     * and then trim trailing white space by iterating over each char
     * beginning to end until space is found and terminating.
     * Wait, if there are leading spaces then it might prematurely end
     * so the best approach would be to first iterate and increment the pointer
     * each time it finds white space. Trimming white space after comes down to
     * loop + indexing until white space since instruction set doesn't use white space
     */

    *line = linebuffer;

    // cut out comment
    char *comment = strstr(*line, "//");
    if (comment != NULL)
        *comment = '\0';

    // fgets always null temrinates so don't worry about the pointer reaching \n, iterating again and causing UB here
    while (isspace((unsigned char)**line)) {
        (*line)++;
    }
    if (**line == '\0')
        return false;
    else if (**line == '(')
        return false;

    char *end = *line;

    // Bug found here, isblank does not include \n and so it remains in line causing upstream problems when assembling, found by inspectings vars at assembler.c in gdb
    // Use isspace instead of isblank
    while (!isspace((unsigned char)*end) && *end != '\0')
        end++;
    *end = '\0';
    return true;
}
