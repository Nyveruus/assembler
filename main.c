/* * Each insruction corresponds to 16 symbolic bits (char representation), * open each file, initialize opcode table, initialize symbol table, add predefined symbols to symbol table, * read line by line one buffer for all, for each line (first pass) check for labels and add to symbol table according to instruction number of next,
 * restart reading, for each line, a or c command?, parse into fields, if a command, notes symbol into symbol table, translate, if symbol found, translate directly,
 * if c command ,translate fields and append, write line
 */
#include <stdio.h>
#include "tables.h"

int main(int argc, char *argv[]) {
   if (argc !=  3) {
       fprintf(stderr, "Usage: hack_assembler [infile] [outfile]\n");
       return 1;
   }
   FILE *infile = fopen(argv[1], "r");
   if (!infile) {
      fprintf(stderr, "Error: invalid path\n");
      return 1;
   }

   //init tables
   symbol symboltable[MAX_SYMBOLS];
   symbolt_init(symboltable);
}


