#include <stdio.h>
#include <stdlib.h>
union _all {
   int   ival;
   char cval;
   //char  sval[4];
   //float fval;
   //unsigned int uval;
};

int main(int argc, char const *argv[])
{
	union _all a;
	a.ival=0x00;
	printf("%x\n",a.ival );//less significant bit comes first
	printf("%c\n", a.cval);

	return 0;
}