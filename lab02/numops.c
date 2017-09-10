// A simple shell for doing bit-oriented operations
// COMP1521 17s2 Week 02 Lab
// Written by John Shepherd, July 2017

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "Numbers.h"

#define  DEFAULT_Nnumbers 64
#define  MAX_LINE      500

#define  bad2Args(a,b,c,d)  ((c = opIndex(a)) < 0 || (d = opIndex(b)) < 0)

void processOptions(int, char **, int *);
int  argIndex(char name);
int  getArgs(char a, int *b, char c, int *d, char e, int *f);
void printHelp();
void trim(char *);

int main(int argc, char *argv[])
{
   int nnumbers;      // size of Numbers objects
   Numbers numbers[26];  // array of Numbers objects named a,b,c,d,...
   char b1;        // name of 1st Numbers on input line
   int  i1;        // index of 1st Numbers on input line
   char b2;        // name of 2nd Numbers on input line
   int  i2;        // index of 2nd Numbers on input line
   char b3;        // name of 3rd Numbers on input line
   int  i3;        // index of 3rd Numbers on input line
   int  shift;     // how far to shift
   char val[MAX_LINE];  // string for literal bit values
   char line[MAX_LINE]; // command line buffer
   
   // process Unix command-line args
   processOptions(argc, argv, &nnumbers);

   // set up zero'd Numbers objects
   for (int i = 0; i < 26; i++) numbers[i] = makeNumbers(nnumbers);

   // loop to read-and-execute commands on Numbers objects
   
   printf("BitOps> ");
   while (fgets(line,MAX_LINE,stdin) != NULL) {
      // if running from a script, show the command
      if (!isatty(0)) fputs(line,stdout);
      // trim spurious spaces
      trim(line);
      // left shift
      if (sscanf(line, "%c = %c << %d", &b1, &b2, &shift) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,0,0)) continue;
         if (shift < 0) { printf("Invalid shift\n"); continue; }
         leftShiftNumbers(numbers[i2], shift, numbers[i1]);
         showNumbers(numbers[i1]); printf("\n");
      }
      // right shift
      else if (sscanf(line, "%c = %c >> %d", &b1, &b2, &shift) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,0,0)) continue;
         if (shift < 0) { printf("Invalid shift\n"); continue; }
         rightShiftNumbers(numbers[i2], shift, numbers[i1]);
         showNumbers(numbers[i1]); printf("\n");
      }
      // bitwise AND
      else if (sscanf(line, "%c = %c & %c", &b1, &b2, &b3) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,b3,&i3)) continue;
         andNumbers(numbers[i2], numbers[i3], numbers[i1]);
         showNumbers(numbers[i1]); printf("\n");
      }
      // bitwise OR
      else if (sscanf(line, "%c = %c | %c", &b1, &b2, &b3) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,b3,&i3)) continue;
         orNumbers(numbers[i2], numbers[i3], numbers[i1]);
         showNumbers(numbers[i1]); printf("\n");
      }
      // bitwise NEG
      else if (sscanf(line, "%c = ~ %c", &b1, &b2) == 2) {
         if (!getArgs(b1,&i1,b2,&i2,0,0)) continue;
         invertNumbers(numbers[i2], numbers[i1]);
         showNumbers(numbers[i1]); printf("\n");
      }
      // assignment
      else if (sscanf(line, "set %c = %s", &b1, val) == 2) {
         if ((i1 = argIndex(b1)) < 0) continue;
         if (strlen(val) == 1 && islower(val[0])) {
            // assign from variable
            i2 = argIndex(val[0]);
            setNumbersFromNumbers(numbers[i2], numbers[i1]);
         }
         else {
            // assign from constant bit-string
            setNumbersFromString(numbers[i1], val);
         }
      }
      // display
      else if (sscanf(line, "show %c", &b1) == 1) {
         if ((i1 = argIndex(b1)) < 0) continue;
         showNumbers(numbers[i1]); printf("\n");
      }
      else if (line[0] == '?') {
         printHelp();
      }
      else if (line[0] == 'q') {
         break;
      }
      else if (line[0] == '\0') {
         /* ignore empty "command */ ;
      }
      else {
         printf("Invalid command\n");
      }
      printf("BitOps> ");
   }
   printf("\n");
   for (int i = 0; i < 26; i++) freeNumbers(numbers[i]);
   return EXIT_SUCCESS;
}

// Process Unix command-line args
void processOptions(int argc, char **argv, int *nnumbers)
{
   int status;

   if (argc < 2) {
      *nnumbers = DEFAULT_Nnumbers;
      return;
   }
   // why don't we need &nnumbers??
   status = sscanf(argv[1], "%d", nnumbers);

   if (status < 1 || *nnumbers < 8) {
      fprintf(stderr,"%s: Need at least 8 numbers\n", argv[0]);
      exit(EXIT_FAILURE);
   }
}

// Converts a Numbers name (a,b,c,d,...,x,y,z) into an index
// Returns index or -1 if name not valid
int argIndex(char name)
{
   if ('a' <= name && name <= 'z')
      return (name-'a');
   else
      return -1;
}

// Processes Numbers names from input line
// converts them to indexes in the Numbers[] array
// if any name is invalid, returns false, otherwise true
int getArgs(char a, int *b, char c, int *d, char e, int *f)
{
   int bad = 0;
   *b = argIndex(a);
   if (*b < 0) {
      printf("Invalid object name: %c\n", a);
      bad++;
   }
   *d = argIndex(c);
   if (*d < 0) {
      printf("Invalid object name: %c\n", c);
      bad++;
   }
   if (e != 0) {
      *f = argIndex(e);
      if (*d < 0) {
         printf("Invalid object name: %c\n", e);
         bad++;
      }
   }
   return (bad == 0);
}

// Remove leading and trailing space from a string
void trim(char *str)
{
   char *s, *t, *w;
   if (str == NULL) return;
   // find first non-space
   s = str;
   while (isspace(*s) && *s != '\0') s++;
   // find last non-space
   t = &s[strlen(s)-1];
   // copy trimmed data into position
   while (isspace(*t) && t > s) t--;
   w = str;
   while (s <= t) { *w = *s; w++; s++; }
   *w = '\0';
}

// Print a help message
void printHelp()
{
   printf("NumOps has 26 bit-string registers named (a..z)\n");
   printf("You can perform various operations on those regisers\n");
   printf("\nCommands: \n");
   printf("X = Y << Number\n");
   printf("X = Y >> Number\n");
   printf("X = Y & Z\n");
   printf("X = Y | Z\n");
   printf("X = ~ Y\n");
   printf("set X = Y\n");
   printf("set X = Bit-string\n");
   printf("show X\n");
   printf("where X,Y,Z are replaced by any lower-case letter\n");
}
