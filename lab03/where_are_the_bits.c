// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 1,
                b : 8,
                c : 23;
};


union float_bit {
  float f;

  struct _bit_fields x;
};
 void print_binary(unsigned int number);
int main(void)
{
  //struct _bit_fields m=NULL;
  union float_bit da;
    //da.x = m;
  da.f = 2.5;

  print_binary(da.x.a);
  printf("\n");
  print_binary(da.x.b);
   printf("\n");
  print_binary(da.x.c);
   printf("\n");
  printf("  %d  , %d  ,  %d  \n",da.x.a, da.x.b, da.x.c);


  //as the float should be stored as sign . exp . frac structure
  //so 2.5 should be 0 01111111 01000000000
  // so its layout is backforwards.


   return 0;
}

 void print_binary(unsigned int number)
{
    if (number) {
        print_binary(number >> 1);
        putc((number & 1) ? '1' : '0', stdout);
    }
}

  
//printf("%p",&da.x.a);


//  struct _bit_fields x;
//   x.a=1;
//   x.b=(1<<2)+1;
//   x.c=(1<<10)+(1<<3)+1;
//   printf("%lu\n",sizeof(x));
//   unsigned int *b = (unsigned int *) &x;
//>??

// printf("the pointer of struct %p \n",&x);
// printf("the struct of a b is %d \n",(int)&x.a);
//   printf("the struct of b c is %d \n",(int)(&x.b-&x.c));
//   printf("the struct of a c is %d \n",(int)(&x.a-&x.c));
//   printf("The value ");
////printf("the random a %u \n",x.a);
////printf("the random b %u \n",x.b);
////printf("the random c %u \n",x.c);

//printf("the random a %lu \n",sizeof(x.a));
//printf("the random b %u \n",x.b);
//printf("the random c %u \n",x.c);

