#include <unistd.h>
#include <stdio.h>

int main(void)
{
   int pid;

   if ((pid = fork()) != 0) {
      int i; char c;
      setbuf(stdout, NULL);
      for (i = 0; i < 100; i++) {
         c = 'a' + i%26;
         putchar(c);
         if (c == 'z') putchar('\n');
      }
      putchar('\n');
   }
   else {
      int i; char c;
      setbuf(stdout, NULL);
      for (i = 0; i < 100; i++) {
         c = 'A' + i%26;
         putchar(c);
         if (c == 'Z') putchar('\n');
      }
      putchar('\n');
   }
   return 0;
}