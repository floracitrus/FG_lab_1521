// make_a_float ... read in bit strings to build a float value
// COMP1521 Lab03 exercises
// Written by John Shepherd, August 2017
// Completed by ...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#define  EXP 8
#define FRAC 23
#define SIGN 1
typedef uint32_t Word;

struct _float {
   // define bit_fields for sign, exp and frac
   // obviously they need to be larger than 1-bit each
   // and may need to be defined in a different order
   unsigned int frac:23,exp:8,sign:1;
};
typedef struct _float Float32;

union _bits32 {
   float   fval;  // interpret the bits as a float
   Word    xval;  // interpret as a single 32-bit word
   Float32 bits;  // manipulate individual bits
};
typedef union _bits32 Union32;

void    checkArgs(int, char **);
Union32 getBits(char *, char *, char *);
char   *showBits(Word, char *);

int main(int argc, char **argv)
{
   union _bits32 u;
   char out[50];

   // here's a hint ...
   u.bits.sign = u.bits.exp = u.bits.frac = 0;
   //Mycomments, so this main function make all the bits to 0
   // check command-line args (all strings of 0/1
   // kills program if args are bad
   checkArgs(argc, argv);

   // convert command-line args into components of
   // a Float32 inside a Union32, and return the union
   u = getBits(argv[1], argv[2], argv[3]);

   printf("bits : %s\n", showBits(u.xval,out));
   printf("float: %0.10f\n", u.fval);

   return 0;
}

// convert three bit-strings (already checked)
// into the components of a struct _float
Union32 getBits(char *sign, char *exp, char *frac)
{
   Union32 new;

   // this line is just to keep gcc happy
   // delete it when you have implemented the function
   new.bits.sign = new.bits.exp = new.bits.frac = 0;
   // convert char *sign into a single bit in new.bits
   new.bits.sign = sign[0] - '0';
   // convert char *exp into an 8-bit value in new.bits  
   for(int i=0;i<=7;i++){
        new.bits.exp += (exp[i]-'0')<<(7-i);
    }
   
   for(int i=0;i<=22;i++){
      new.bits.frac += (frac[i]-'0')<<(22-i);
   }

   return new;
}

// convert a 32-bit bit-stringin val into a sequence
// of '0' and '1' characters in an array buf
// assume that buf has size > 32
// return a pointer to buf
char *showBits(Word val, char *buf)
{
//signs
   buf[0] = (val >> 31) + '0';
   buf[1] = ' ';
//exponention
   for(int i = 2; i <= 9 ; i++){
      int count = 0;

      buf[i] = val << (1+count);
      Word temp = temp >> 31;
      //printf("temp is %d",temp);
      buf[i] =temp + '0';
      count++;
   }
   buf[10]=' ';
//fractional 
   for(int i = 11;i<=33; i++){
      int count = 0;
      buf[i] = (val << (9+count) >>31) +'0';
      count++;
   }
   buf[34]='\0';

   return buf;
}

// checks command-line args
// need at least 3, and all must be strings of 0/1
// never returns if it finds a problem
void checkArgs(int argc, char **argv)
{
   int justBits(char *, int);

   if (argc < 3) {
      printf("Usage: %s Sign Exp Frac\n", argv[0]);
      exit(1);
   }
   if (!justBits(argv[1],1)) {
      printf("%s: invalid Sign\n", argv[0]);
      exit(1);
   }
   if (!justBits(argv[2],8)) {
      printf("%s: invalid Exp: %s\n", argv[0], argv[2]);
      exit(1);
   }
   if (!justBits(argv[3],23)) {
      printf("%s: invalid Frac: %s\n", argv[0], argv[3]);
      exit(1);
   }
   return;
}

// check whether a string is all 0/1 and of a given length
int justBits(char *str, int len)
{
   if (strlen(str) != len) return 0;

   while (*str != '\0') {
      if (*str != '0' && *str != '1') return 0;
      str++;
   }
   return 1;
}
   // for(int shift = 23;shift < 31; shift++){//23 or 24 31 or 30 or32
   //    Word tempExp = val << shift;
   //    tempExp >>= (shift+1);
   //    printf("%d",tempExp);

   // }


   //32-23 = 9 -8 =1
   //|||||||    |0|0|0|1|0|0|0|1|sign|
   //     frac  last  exp first   sign
   




   // convert char *frac into a 23-bit value in new.bits
   // while(*frac){
   //   if(*frac++ == '1') new.bits.frac = 1<<(32-i);
   //}
// if((val>>31)==1){
//       printf("-");
//       //and set it to 0 as it may easier in future.
//       val = val ^ 1; 
   //}
 // while(*exp){
   //   new.bits.exp <<= 1;
     // if(*exp++ == '1') new.bits.exp +=1;
  // }
  // printf("%s",exp);
  // printf("%d",new.bits.exp);
