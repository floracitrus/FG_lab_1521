#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXLINE 500
void copyInput(char * );
int main(int argc, char *argv[]){
    pid_t pid;
    int stat;
    pid = fork();
    printf("pid is %d\n", pid);
    if(pid != 0){
        wait(&stat);
        //copyInput("Parent");
        printf("parent process\n");

    }
    else{
        printf("child process");
        //        copyInput("child");
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
      sleep(1);
      //sleep(random()%3);
   }
   printf("%s quitting\n", name);
   return;
}
