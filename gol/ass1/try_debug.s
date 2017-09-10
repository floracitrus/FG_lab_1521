# board.s ... Game of Life on a 10x10 grid

   .data

N: .word 10  # gives board dimensions

board:
   .byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
   .byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0
   .byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0

newBoard: .space 100
# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by <<Flora>>, August 2017
########global datas
   .data
   .align 2
main_ret_save: .space 4
msg1:
  .asciiz   "# Iterations: "
msg2:
  .asciiz   "EQUALLL=== After iteration "
msg3:
  .asciiz   " ===\n"

#main program

  .data
    .align 2
main_tmp0_save:
    .space 4
  
  .data
    .align 2
main_tmp1_save:
    .space 4

  .data
    .align 2
main_tmp2_save:
    .space 4

   .text
   .globl main


main:
la    $a0, msg1   #printf iterations
li    $v0, 4       
syscall  

#li   $s2, 10
lw     $s2,N
lb     $s5, N
beq   $s5, $s2, equalla

equalla:
la   $a0, msg2
li   $v0, 4
syscall

#li   $s3, 10
lw    $s3, N
# row = 0
li   $s0, 0
loop_outer:
  # if row == nrows, end outer loop
  beq  $s0, $s2, end_loop_outer

  # col = 0
  li   $s1, 0
loop_inner:

     # if col == ncols, end inner loop
    beq  $s1, $s3, end_loop_inner

    # convert [row][col] to byte offset
    # t0 = row * ncols
    mul  $t0, $s0, $s3
    # t0 = (row * ncols) + col
    add  $t0, $t0, $s1
     # a0 = *(flag_addr + t1) # load the byte located at address: flag+$t1
    lb   $a0, board($t0)

     # printf("%c", flag[row][col])
    li   $v0, 11
    syscall

     # col++
    addi $s1, $s1, 1
    j    loop_inner

end_loop_inner:
        # printf("\n")
       li   $a0, '\n'
       li   $v0, 11
       syscall

       # row++
       addi $s0, $s0, 1
       j    loop_outer

end_loop_outer:
lw    $ra, main_ret_save  
jr    $ra       #end of main
