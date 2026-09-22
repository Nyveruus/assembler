/* Each insruction corresponds to 16 symbolic bits (char representation), * open each file, initialize opcode table, initialize symbol table, add predefined symbols to symbol table, * read line by line one buffer for all, for each line (first pass) check for labels and add to symbol table according to instruction number of next,
 * restart reading, for each line, a or c command?, parse into fields, if a command, notes symbol into symbol table, translate, if symbol found, translate directly,
 * if c command ,translate fields and append, write line
 */

#include <stdio.h>
#include <string.h>
#include "tables.h"
#include "parser.h"
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

   FILE *outfile = fopen(argv[2], "w");
   if (!outfile) {
       perror("Error: ");
       return 1;
   }

   //init tables, fieldtable is already global

   symbol symboltable[MAX_SYMBOLS];
   symbolt_init(symboltable);

   /* Do a loop for reading each line and parsing, before the parser step check for whitespace or comments,
    * ignore it from read, and if nothing then continue (empty line)?
    */

   char linebuffer[LINE_LEN];
   char *line;
   size_t instruction_count = 0, line_n = 0;

   /* first pass, look for labels, if find (x) in line, update symboltable with x for name and isntruction_count for value, else
    * line has chars, then instruction count++
    */

   while (fgets(linebuffer, sizeof(linebuffer), infile) != NULL) {
       first_pass_func(linebuffer, symboltable, &instruction_count);
   }

   rewind(infile);

    //second pass
    while (fgets(linebuffer, sizeof(linebuffer), infile) != NULL) {
        line_n++;
        //strip white space and comments
        if (!parser(linebuffer, &line))
            continue;

        /* assemble, continuously append to a new symbolic bits buffer, lookup and write in order of bit fields
         * and use = ; or their absence as delimiters for each field, when bit buffer is complete, write to file.
         * If syntax error, output line number with line_n, don't write to file, close file, rename to .partial
         */


   }
}


