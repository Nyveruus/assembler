/* Each insruction corresponds to 16 symbolic bits (char representation), * open each file, initialize opcode table, initialize symbol table, add predefined symbols to symbol table, * read line by line one buffer for all, for each line (first pass) check for labels and add to symbol table according to instruction number of next,
 * restart reading, for each line, a or c command?, parse into fields, if a command, notes symbol into symbol table, translate, if symbol found, translate directly,
 * if c command ,translate fields and append, write line
 */

#include <stdio.h>
#include <string.h>
#include "tables.h"
#define LINE_LEN 256

int main(int argc, char *argv[]) {
   if (argc !=  3) {
       fprintf(stderr, "Usage: hack_assembler [infile] [outfile]\n");
       return 1;
   }
   FILE *infile = fopen(argv[1], "r");
   if (!infile) {
      perror("Error: ");
      return 1;
   }

   //init tables, fieldtable is already global

   symbol symboltable[MAX_SYMBOLS];
   symbolt_init(symboltable);

   /* Do a loop for reading each line and parsing, before the parser step check for whitespace or comments,
    * ignore it from read, and if nothing then continue (empty line)?
    */

   //read line
    char linebuffer[LINE_LEN];
    size_t instruction_count = 0;
    while (fgets(linebuffer, sizeof(linebuffer), infile) != NULL) {

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
            continue;

        char *end = line;
        while (isspace((char)*end) && *end != NULL)
            end++;
        *end = '\0';

        parser(line);
    }
}


