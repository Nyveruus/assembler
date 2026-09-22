#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static bool preprocess(char *linebuffer);

bool parser(char *linebuffer) {
    //remove comments, whitespace
    if (!preprocess)
        return false;
}

static bool preprocess(char *linebuffer) {

    /* Use a pointer for moving around the buffer, first check for any comments (//), set it to null terminator
     * and then trim trailing white space by iterating over each char
     * beginning to end until space is found and terminating.
     * Wait, if there are leading spaces then it might prematurely end
     * so the best approach would be to first iterate and increment the pointer
     * each time it finds white space. Trimming white space after comes down to
     * loop + indexing until white space since instruction set doesn't use white space
     */

    char *line = linebuffer;

    //cut out comment

    char *comment = strstr(line, "//");
    if (comment != NULL) {
        *comment = '\0';
    }

    //fgets always null temrinates so don't worry about the pointer reaching \n, iterating again and causing UB

    while (isspace((char)*line)) {
        line++;
    }
    if (*line == '\0')
        return false;

    char *end = line;
    while (isspace((char)*end) && *end != '\0')
        end++;
    *end = '\0';
    return true;
}
