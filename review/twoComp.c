#include<stdio.h>
#include<stdlib.h>
int main(void){
	int val = 1111;
	//two's complement
	int bits = 32;
	if(val & 1<<31){
		val = val - (1 << bits);
	}

	printf("%d", val);

	return 0;
}

