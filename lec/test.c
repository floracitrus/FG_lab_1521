#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
int main(void)
{
   pid_t id;  int stat;

   if ((id = fork()) != 0) {
      printf("A = %d\n", id);
      printf("stat is %d",stat);
      wait(&stat);
      printf("stat is %d",stat);
      return 1;
   }
   else {
      printf("B = %d\n", getppid());
      printf("%10.4lf\n", (double)2.718281828459);
      printf("%20.20lf\n", (double)4.0/7);
      return 0;
   }
}