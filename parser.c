#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static bool preprocess(char *linebuffer, char **line);

bool parser(char *linebuffer, char **line, size_t *instruction_count) {
    //remove comments, whitespace. If not just white space or comment, increment instruction count
    if (!preprocess(linebuffer, line))
        return false;
    (*instruction_count)++;
}

static bool preprocess(char *linebuffer, char **line) {

    /* Use a pointer for moving around the buffer, first check for any comments (//), set it to null terminator
     * and then trim trailing white space by iterating over each char
     * beginning to end until space is found and terminating.
     * Wait, if there are leading spaces then it might prematurely end
     * so the best approach would be to first iterate and increment the pointer
     * each time it finds white space. Trimming white space after comes down to
     * loop + indexing until white space since instruction set doesn't use white space
     */

    *line = linebuffer;

    //cut out comment

    char *comment = strstr(*line, "//");
    if (comment != NULL) {
        *comment = '\0';
    }

    //fgets always null temrinates so don't worry about the pointer reaching \n, iterating again and causing UB here
    while (isspace((char)**line)) {
        (*line)++;
    }
    if (**line == '\0')
        return false;

    char *end = *line;
    while (!isspace((char)*end) && *end != '\0')
        end++;
    *end = '\0';
    return true;
}
