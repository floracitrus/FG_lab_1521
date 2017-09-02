# COMP1521 Lab 04 ... Simple MIPS assembler


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
   la   $a0, msg1
   li   $v0, 4
   syscall
   li   $v0, 5
   syscall
   move $a0, $v0

   jal  fac
   move $t3, $v0

   la   $a0, msg2
   li   $v0, 4
   syscall
   move $a0, $t3
   li   $v0, 1
   syscall
   la   $a0, eol
   li   $v0, 4
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

   li   $t0, 1 # f
   li   $t1, 1 # i

loop:
   bge  $t1, $a0, exit
   addi $t1, $t1, 1
   mul  $t0, $t0, $t1
   j    loop

exit:
   move $v0, $t0
   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)

