// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
   struct _bit_fields x;

   x.a = 1;
   x.b = (1 << 2) + 1;
   x.c = (1 << 4) + (1 << 2) + 1;
   unsigned int *b = (unsigned int *) &x;
   for (int i = 0; i < 32; i++)
       printf("%u", (*b) << i >> 31);
   printf("\n");
   printf("%ld\n",sizeof(x));

   return 0;
}
