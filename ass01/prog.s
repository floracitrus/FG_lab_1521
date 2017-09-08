# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by ZHENYU YAO, z5125769, 2017-09


# usage of registers
# $s0 user-input maxiters
# $s1 constant N
# $s2 address of board
# $s3 address of newboard
# $s4 nn
# $t0 main first-layer counter, n
# $t1 main second-layer counter, i
# $t2 main third-layer counter, j
# $t3 handle memory location
# $t4 handle memory location
# $t5 handle memory location
# $t6 sub outter counter and constant 0
# $t7 sub inner counter and constant 1


   .data
   .align 2
main_ret_save: 
   .space 4
msg1:
   .asciiz "# Iterations: "
msg2:
   .asciiz "=== After iteration "
msg3:
   .asciiz " ===\n"

   .text
   .globl main
main:
   sw   $ra, main_ret_save

   la   $a0, msg1             # print "# Iterations: \n"
   li   $v0, 4
   syscall
   li   $v0, 5                # input maxiters 
   syscall
   move $s0, $v0              # $s0 = maxiters
   lw   $s1, N                # $s1 = N
   la   $s2, board            # $s2 = addr[board]
   la   $s3, newBoard         # $s3 = addr[newboard]
   li   $t0, 1                # $t0 = n = 1

loop1:
   bgt  $t0, $s0, end_loop1   # for n in 1..maxiters
   li   $t1, 0                # $t1 = i = 0

loop2:
   bge  $t1, $s1, end_loop2   # for i in 0..N-1
   li   $t2, 0                # $t2 = j = 0

loop3:
   bge  $t2, $s1, end_loop3   # for j in 0..N-1
   move $a0, $t1              # $a0 = i
   move $a1, $t2              # $a1 = j

   jal  neighbours

   move $s4, $v0              # $s4 = nn = neighbours(i, j)
   mul  $t3, $s1, $t1         # $t3 = N*i
   add  $t3, $t3, $t2         # $t3 = N*i+j
   add  $t4, $s2, $t3         # $t4 = addr[board[i][j]]
   add  $t5, $s3, $t3         # $t5 = addr[newboard[i][j]]
   lb   $t4, ($t4)            # $t4 = board[i][j]

   li   $t6, 0                # $t6 = 0
   li   $t7, 1                # $t7 = 1

if1:
   bne  $t4, 1, elif1         # if board[i][j] == 1:

if2:
   bge  $s4, 2, elif2         # if nn < 2:
   sb   $t6, ($t5)            # newboard[i][j] = 0
   j    endif
elif2:
   bge  $s4, 4, else2         # elif nn == 2 or nn == 3:
   sb   $t7, ($t5)            # newboard[i][j] = 1
   j    endif
else2:
   sb   $t6, ($t5)            # else: newboard[i][j] = 0
   j    endif

elif1:
   bne  $s4, 3, else1         # elif nn == 3:
   sb   $t7, ($t5)            # newboard[i][j] = 1
   j    endif
else1:
   sb   $t6, ($t5)            # else: newboard[i][j] = 0
endif:
   addi $t2, $t2, 1           # $t2 = j++
   j    loop3

end_loop3:
   addi $t1, $t1, 1           # $t1 = i++
   j    loop2

end_loop2:
   la   $a0, msg2             # print "=== After Iteration "
   li   $v0, 4
   syscall
   move $a0, $t0              # print n
   li   $v0, 1
   syscall
   la   $a0, msg3             # print " ===\n"
   li   $v0, 4
   syscall

   jal  copy_show

   addi $t0, $t0, 1           # $t0 = n++
   j    loop1

end_loop1:
end_main:
   lw   $ra, main_ret_save
   jr   $ra


   .data
   .align 2
neighbours_ret_save:
   .space 4

   .text
neighbours:
   sw   $ra, neighbours_ret_save

   li   $s4, 0                # $s4 = nn = 0
   li   $t6, -1               # $t6 = x = -1

n_loop1:
   bgt  $t6, 1, end_n_loop1   # for x in -1..1
   li   $t7, -1               # $t7 = y = -1

n_loop2:
   bgt  $t7, 1, end_n_loop2   # for y in -1..1
   addu $t4, $t6, $a0         # $t4 = i+x
   addu $t5, $t7, $a1         # $t5 = j+y

n_if1:
   blt  $t4, 0, end_n_if      # if i+x < 0 or i+x > N-1: continue
   bge  $t4, $s1, end_n_if
n_if2:
   blt  $t5, 0, end_n_if      # if j+y < 0 or j+y > N-1: continue
   bge  $t5, $s1, end_n_if
n_if3:
   bne  $t6, 0, n_if4         # if i+x == 0 and j+y == 0: continue
   bne  $t7, 0, n_if4
   j    end_n_if
n_if4:
   mul  $t4, $s1, $t4         # $t4 = N*(i+x)
   add  $t4, $t4, $t5         # $t4 = N*(i+x)+(j+y)
   add  $t5, $s2, $t4         # $t5 = addr[board[i+x][j+y]]
   lb   $t5, ($t5)            # $t5 = board[i+x][j+y]

   bne  $t5, 1, end_n_if      # if board[i+x][j+y] == 1:
   addi $s4, $s4, 1           # $s4 = nn++

end_n_if:
   addi $t7, $t7, 1           # $t7 = y++
   j    n_loop2

end_n_loop2:
   addi $t6, $t6, 1           # $t6 = x++
   j    n_loop1

end_n_loop1:
end_neighbours:
   move $v0, $s4
   lw   $ra, neighbours_ret_save
   jr   $ra


   .data
   .align 2
copy_show_ret_save:
   .space 4
dot:
   .asciiz "."
sharp:
   .asciiz "#"
eol:
   .asciiz "\n"

   .text
copy_show:
   sw   $ra, copy_show_ret_save
   li   $t6, 0                # $t6 = i = 0

s_loop1:
   bge  $t6, $s1, end_s_loop1 # for i in 0..N-1
   li   $t7, 0                # $t7 = j = 0

s_loop2:
   bge  $t7, $s1, end_s_loop2 # for j in 0..N-1

   mul  $t3, $s1, $t6         # $t3 = N*i
   add  $t3, $t3, $t7         # $t3 = N*i+j
   add  $t4, $s2, $t3         # $t4 = addr[board[i][j]]
   add  $t5, $s3, $t3         # $t5 = addr[newboard[i][j]]
   lb   $t5, ($t5)            # $t5 = newboard[i][j]
   sb   $t5, ($t4)            # board[i][j] = $t5
   lb   $t4, ($t4)            # $t4 = board[i][j]

s_if:
   bne  $t4, 0, s_else        # if board[i][j] == 0:
   la   $a0, dot              # print "."
   li   $v0, 4
   syscall
   j    s_end_if
s_else:
   la   $a0, sharp            # else: print "#"
   li   $v0, 4
   syscall
s_end_if:
   addi $t7, $t7, 1           # $t7 = j++
   j    s_loop2

end_s_loop2:
   la   $a0, eol              # print "\n"
   li   $v0, 4
   syscall
   addi $t6, $t6, 1           # $t6 = i++
   j    s_loop1

end_s_loop1:
end_copy_show:
   lw   $ra, copy_show_ret_save
   jr   $ra
