#include <unistd.h>
#include <stdio.h>

int main(void)
{
   int pid;

   FILE *fp = fopen("Out","w");
   if ((pid = fork()) != 0) {
      int i; char c;
      setbuf(fp, NULL);
      for (i = 0; i < 130; i++) {
         c = 'a' + i%26;
         fputc(c,fp);
         if (c == 'z') fputc('\n',fp);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              #include <unistd.h>
#include <stdio.h>

int main(void)
{
   int pid;

   FILE *fp = fopen("Out","w");
   if ((pid = fork()) != 0) {
      int i; char c;
      setbuf(fp, NULL);
      for (i = 0; i < 130; i++) {
         c = 'a' + i%26;
         fputc(c,fp);
         if (c == 'z') fputc('\n',fp);
      }
      fputc('\n',fp);
   }
   else {
      int i; char c;
      setbuf(fp, NULL);
      for (i = 0; i < 130; i++) {
         c = 'A' + i%26;
         fputc(c,fp);
         if (c == 'Z') fputc('\n',fp);
      }
      fputc('\n',fp);
   }
   return 0;
}
      }
      fputc('\n',fp);
   }
   else {
      int i; char c;
      setbuf(fp, NULL);
      for (i = 0; i < 130; i++) {
         c = 'A' + i%26;
         fputc(c,fp);
         if (c == 'Z') fputc('\n',fp);
      }
      fputc('\n',fp);
   }
   return 0;
}