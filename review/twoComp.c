#include<stdio.h>
#include<stdlib.h>
int main(void){

	//this is print binary
	int i;
	unsigned char v = 20;
	for(i = 7; i>=0; i--){
		putchar('0'+((v>>i)&1));
	}
	//int val = 9;
	////two's complement
	//int bits = 32;
	//if(val & 1<<31){
	//	val = val - (1 << bits);
	//}

	//printf("%d", val);

	return 0;
}

