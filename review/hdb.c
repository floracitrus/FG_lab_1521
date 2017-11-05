#include <stdio.h>
#include <stdlib.h>
typedef unsigned int Word;
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
Word reverseBits(Word w)
{
	Word ret = 0;
  	for (int bit = 0; bit < 32; bit++) {
    	Word wMask = 1 << (31 - bit);
    	Word retMask = 1 << bit;
      	if (w & wMask) {
        	ret = ret | retMask;
      	}
   	}
 
   return ret;
}
int main(int argc, char *argv[]){
	printf("%d = %3o = %2x\n", 127, 127, 127);
	printf("%d = %3o = %2x\n", 15, 15, 15);
	// decimal octal heximal=> use heximal to write binary number by 4 block each
	unsigned short a, b, c;
	a = 0x5555; //0101010101010101
	b = 0xAAAA; //1010101010101010
	//a | b     //1111111111111111 //0xffff 
	//a & b 	//0000000000000000 //0x0000
	//a ^ b 	//1111111111111111 //0xffff
	//a & ~b  	//0101010101010101 //0x5555
	//c << 6   	//0000000001000000 //0x0040
	//a >> 4	//0000010101010101 //0x0555
	//a & (b<<1)//0101010101010100 //0x5554


	c = 0x0001; //0000000000000001 //0x0001
   Word w1 = 0x01234567;
   //0000 => 0000 = 0
   //0001 => 1000 = 8
   //0010 => 0100 = 4
   //0011 => 1100 = C
   //0100 => 0010 = 2
   //0101 => 1010 = A
   //0110 => 0110 = 6
   //0111 => 1110 = E
   assert(reverseBits(w1) == 0xE6A2C480);
   printf("All tests passed!");


	//if(fork()!=0){
	//
	//	printf("open");
	//	int stat;
	//	wait(&stat);
	//	fd=open("new_file",O_READY);
	//	flock(fd,LOCK_EX);
	//	buf="sadf";
	//	write(fd,&buf,size);
	//	flock(fd,LOCK_UN);
	//}else{
	//
	//}

	return 0;
}
