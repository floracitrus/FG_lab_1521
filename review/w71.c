// Functions on Student structs

#include <stdio.h>
#include <string.h>
#include "w71.h"

#define MAXLINE 100

int getStudentData(Student *s)
{
   int  nerrs = 0;
   char resp[MAXLINE];

   printf("ID          : ");
   fgets(resp, MAXLINE, stdin);
//    Following is the declaration for fgets() function.

// char *fgets(char *str, int n, FILE *stream)
// Parameters
// str − This is the pointer to an array of chars where the string read is stored.

// n − This is the maximum number of characters to be read (including the final null-character). 
// Usually, the length of the array passed as str is used.

// stream − This is the pointer to a FILE object that identifies the stream where characters are read from.
// Return Value
// On success, the function returns the same str parameter. 
// If the End-of-File is encountered and no characters have been read, 
// the contents of str remain unchanged and a null pointer is returned.
// If an error occurs, a null pointer is returned.
   // if(sscanf(resp, "%d",&(s->id))){
   //    nerrs++;
   // }
   printf("given name: ");
   //fgets(s->given, MAXNAME, stdin);
   //s->given[strlen(s->given)-1] = '\0';
   // printf("Family name : ");
   // fgets(&(s->family[0]), MAXNAME, stdin);
   // s->family[strlen(s->family)-1] = '\0';
   // printf("Program     : ");
   // fgets(resp, MAXLINE, stdin);
   // if (sscanf(resp, "%d", &(s->prog)) != 1) nerrs++;
   // printf("WAM         : ");
   // fgets(resp, MAXLINE, stdin);
   // if (sscanf(resp, "%f", &(s->wam)) != 1) nerrs++;
// int sscanf(const char *str, const char *format, ...) 
// reads formatted input from a string.
//str − This is the C string that the function processes as its source to retrieve the data.
//    Return Value of sscanf
// On success, the function returns the number of variables filled. 
// In the case of an input failure before any data could be successfully read, 
// EOF is returned.
   return (nerrs > 0) ? -1 : 0;
}

void showStudentData(Student s)
{
   printf("%s %s (%d), studying %d, with wam %0.1f\n",
          s.family, s.given, s.id, s.prog, s.wam);
}