#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"
#include "parser.h"
#include "assembler.h"
#define LINE_LEN 256

char *append_partial(char *name);

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

   /*
    * Do a loop for reading each line and parsing, before the parser step check for whitespace or comments,
    * ignore it from read, and if nothing then continue (empty line)?
    */

   char linebuffer[LINE_LEN];
   char *line, partial_name;
   size_t instruction_count = 0;
   ssize_t line_n;

   /*
    * first pass, look for labels by clearing comments and white space and then checking if current char is (, a label,
    * update symboltable with everything between () for name and instruction_count for value, if there is a different char than (,
    * we can just increment counter and return
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

        /*
         * assemble, we should append to a new symbolic bits buffer as we lookup and translate parts of the instruction. We can
         * use = ; or their absence as delimiters for each field and when bit buffer is complete, write to file.
         * If there is a syntax error, just output line number with line_n and don't write, close file, rename to .partial or just delete the outfile
         */

        char buffer[17];
        buffer[16] = '\0';
        if (!assemble(buffer, line, symboltable))  {
            fprintf(stderr, "Syntax error: line %zd\n", line_n);
            if (!(partial_name = append_partial(argv[2]))) {
                fclose(outfile);
                remove(argv[2]);
                goto error_cleanup;
            }

            fclose(outfile);
            rename(argv[2], partial_name);
            free(partial_name);
error_cleanup:
            fclose(infile);
            return 1;
        }
        fprintf(outfile, "%s\n", buffer);
    }
    fclose(outfile);
    fclose(infile);
    return 0;
}

char *append_partial(char *name) {

}


