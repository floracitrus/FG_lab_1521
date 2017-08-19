#include<stdio.h>
int main(void){
    char * str="0";
    char * str1 = {"1"};
    int a = str-"0";
    int b = "1"-"0";
    int c = str1-"0";
    printf("%d, %d, %d ",a,b,c);
    return 0;
}
