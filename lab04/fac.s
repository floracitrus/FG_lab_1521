# COMP1521 Lab 04 ... Simple MIPS assembler
#include <stdio.h>
#include <stdlib.h>
 
#int fac(int);

#int main(void)
#{
#   int n;
#   printf("n: ");
#   scanf("%d", &n);
#   printf("n! = %d\n", fac(n));
#   return 0;
#}
# 
#int fac(int k)
#{
#   int i, f = 1;
#   for (i = 1; i <= k; i++) f = f * i;
#   return f;
#}

### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function

   .data
   .align 2
main_ret_save:
   .word 4

   .text
   .globl main

main:
   sw   $ra, main_ret_save

#  ... your code for main() goes here

   la   $a0, msg1
   li   $v0, 4        # printf("n: ");
   syscall            # get an integer
   li $v0, 5
   syscall
   move $t0, $v0
   la   $a0, msg2
   li   $v0, 4        # printf("n!= ");
   syscall    
   jal  fac
   li $v0, 1 #????   #pinrtf("%d");
   syscall
   la   $a0, eol
   li   $v0, 4        # printf("\n");
   syscall


   lw   $ra, main_ret_save
   jr   $ra           # return

### fac() function

   .data
   .align 2
fac_ret_save:
   .space 4

   .text

fac:
   sw   $ra, fac_ret_save
   addi $a0,$t0, 0 #not too sure if t0 added into a0
   li $t1, 1
   li $t2, 1
   loop:
      beq $t1, $t0, exit
      mul $t2, $t2, $t1
      addi $t1,$t1,1
      j loop
   exit:
#  ... your code for fac() goes here
   
   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)

