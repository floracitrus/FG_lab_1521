# COMP1521 Practice Prac Exam #1
# int rmOdd(int *src, int n, int*dest)
# int rmOdd(int *src, int n, int *dest)
# {
#    int i, j = 0;
#    for (i = 0; i < n; i++) {
#       if (src[i]%2 == 0) {
#          dest[j] = src[i];
#          j++;
#       }
#    }
#    return j;
# }
   .text
   .globl rmOdd

# params: src=$a0, n=$a1, dest=$a2
rmOdd:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   addi $sp, $sp, -4
   sw   $s0, ($sp)
   
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...
   li $t0, 0 #i=0
   li $t1, 0 #j=0
   li $t5, 2 
for:
   bge $t0, $a1, endfor #i>=n then jump out of the loop   
   mul $t3, $t0, 4 #4*i
   add $t2, $a0, $t3 #t2 = src+4*i
   lw $t7, 0($t2)  #load word to $t7
   rem $t4, $t2, $t5
   beq $t4, 0, if
   bne $t4, 0, increment
if:
   mul $t3, $t1, 4 #4*i
   add $t4, $a2, $t3 #t2 = src+4*i
   sw $t7, 0($t4)  #load word at $t4
   addi $t1, $t1, 1
   j increment

increment:
   addi $t0, $t0, 1

endfor:
   move $v0, $t1   


   # add code for your rmOdd function here

# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   
   j    $ra

