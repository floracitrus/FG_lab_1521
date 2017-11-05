// COMP1521 17s2 Lab08 ... processes competing for a resource
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define MAXLINE BUFSIZ

void copyInput(char *);

int main(void)
{
   struct sigaction act;
   memset (&act, 0, sizeof(act));
   //signal (SIGINT, SIG_IGN);
   if (fork() != 0) {
      signal (SIGINT, SIG_IGN);
      copyInput("Parent");
   }
   else if (fork() != 0) {
      //step1
      signal (SIGINT, SIG_DFL);

      copyInput("Child");

   }
   else {
      //signal (SIGINT, SIG_DFL);
      copyInput("Grand-child");
   }
   return 0;
}

void copyInput(char *name)
{
   pid_t mypid = getpid();
   char  line[MAXLINE];
   printf("%s (%d) ready\n", name, mypid);
   while (fgets(line, MAXLINE, stdin) != NULL) {
      printf("%s: %s", name, line);
      sleep(2);
      //sleep(random()%3);
   }
   printf("%s quitting\n", name);
   return;
}
