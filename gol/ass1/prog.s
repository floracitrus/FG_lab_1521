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
	.asciiz		"# Iterations: "
msg2:
	.asciiz		"=== After iteration "
msg3:
	.asciiz 	" ===\n"

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
   	sw		$ra, main_ret_save
   	la		$a0, msg1		#printf iterations
   	li 		$v0, 4       
   	syscall           
   	li 		$v0, 5        	#scanf
   	syscall					#v0 is maxiters now
   	move 	$s1, $v0 		#s1 = maxiters
   	li 		$t0, 1			#$t0=n=1
   	la 		$s0, N			#$s0=N 
   	
   	jal 	copyBackAndShow
   	li 		$s3, 1			#static int for comparision
   	li 		$s4, 2			#static int for comparision 
   	li 		$s5, 3			#static int for comparision
 
   	li 		$t5, 0			#init $t5=0

   	

main_loop1:	
	bgt 	$s1, $t0, main_loop1_end  	#if(n<=max)=>(max>n)
	li 		$t1, 0						#$t1=i

main_loop2:

	blt 	$t1, $s0, main_loop2_end	#if i<N
	li 		$t2, 0						#$t2=j

main_loop3:

	blt 	$t2, $s0, main_loop3_end    #if j<N

	move $a2,$t1 			#arg2 with i
	move $a3,$t2 			#arg3 with j
	jal neighbours			#int nn = neighbours(i,j);
	move $t8, $v0			#get the return value v0 to t8 t8=nn now



	mul 	$t5, $t2, $s0	 		#$t5 = N*j
	add 	$t5, $t5, $t1	 		#$t5 = N*j+i
	#add 	$t5, $s1, $t5 	 		#$t5 = base + N*j+i = board[i][j]
	lb 		$t3, board($t5)   			#

	li 		$s3, 1
	li 		$s4, 2
	li 		$s5, 3					#as static been compared to others
main_if:
	
	beq 	$t3, $s3, main_inner_if 
	beq 	$t8, $s5, equal_tri 	#outer_else_if
	sb  	$0, 0($t6)
	#li 		$t6, 0 					#else newBoard[i][j]=0

main_inner_if:
	mul 	$t6, $t2, $s0	 #$t6 = N*j
	add 	$t6, $t6, $t1	 #$t6 = N*j+i
	add 	$t6, $s2, $t6 	 #$t6 = Newbase + N*j+i = newBoard[i][j]

	blt 	$t8, $s4, less_two		#if
	beq 	$t8, $s4, equal_two_tri #else if
	beq 	$t8, $s5, equal_two_tri #else if
	###not sure if there needed anything else
	li 		$t4, 0 					#else newBoard[i][j]=0
	addi 	$t2, $t2, 1

less_two:
	sb  	$0, 0($t6)
	#li 		$t6, 0
	#addi 	$t2, $t2, 1
	j 		main_loop3
equal_two_tri:
	sb 		$s3, 0($t6)
	#li 		$t6, 1
	#addi 	$t2, $t2, 1
	j 		main_loop3
equal_tri:
	sb 		$s3, 0($t6)
	#li 		$t6, 1
	#addi 	$t2, $t2, 1
	j 		main_loop3 		#maybe can be merged latter on

main_loop3_end:
	addi 	$t1, $t1, 1
	j 		main_loop2
main_loop2_end:
	addi 	$t0, $t0, 1
	j 		main_loop1

	la		$a0, msg2		#printf after interation
   	li 		$v0, 4 
   	syscall
   	move 	$a0, $t0
   	li 		$v0, 1 			#printf n
   	syscall
   	la 		$a0, msg3
   	li 		$v0, 4
   	syscall
   	jal 	copyBackAndShow

main_loop1_end:
   	lw   	$ra, main_ret_save  
   	jr   	$ra 			#end of main




 	.data
    .align 2
nei_ret_save:
    .space 4

    .text
#void neighbours a2=i, a3=j
neighbours:
	sw   	$ra, nei_ret_save
	li 		$t9, 0							#t9=nn
	li 		$s3, 1							#s3=1
	li 		$t3, -1							#t3=x=-1
nei_outer_loop:
    bgt 	$s3, $t3, nei_outer_loop_end	#1>=x
    li 		$t4, -1							#t4=y=-1
nei_inner_loop:
	bgt 	$s3, $t4, nei_inner_loop_end 	#1>=y
	
	add 	$t7, $a0, $t3					#$t7 = i+x
	blt 	$t7, $0, ct_increment 			#$t7<0 => y++ 
	sub 	$s6, $s0, $s3					#$s6=N-1
	bgt		$t7, $s6, ct_increment

	add 	$t8, $a3, $t4					#t8 = j+y
	blt 	$t8, $0, ct_increment 			#$t8<0 => y++ 
	sub 	$s6, $s0, $s3					#$s6=N-1
	bgt		$t8, $s6, ct_increment

	beq 	$t3, $0, check_y_zero			#if x==0 && y==0

	mul 	$t5, $t8, $s0	 				#$t5 = (j+y)*N
	add 	$t5, $t5, $t7	 				#$t5 =(j+y)*N+(i+x)
	add 	$t5, $s1, $t5 	 				#$t5 = baseAdr + (j+y)*N+(i+x)
	sb 		$s8, board($t5)
	
	beq 	$s8, $s3, result_increment
check_y_zero:
	beq 	$t4, $0, ct_increment

ct_increment:
	addi 	$t4, $t4, 1
	j 		nei_inner_loop
result_increment:
	addi 	$t9, $t9, 1 					#nn++;
	addi 	$t4, $t4, 1						#get increment to inner loop
	j 		nei_inner_loop

nei_inner_loop_end:
	addi 	$t3, $t3, 1
	j 		nei_outer_loop

nei_outer_loop_end:
	move $v0,$t9
	lw   $ra, nei_ret_save
	jr   $ra            					# return ($v0)



#void cp()
copyBackAndShow:
	lw 		$s0, N			#$s0=N 
	li 		$t3, 0 			#outer for loop couter i

cp_outer_loop:
	# i<N
	blt 	$t3, $s0, cp_outer_loop_end
	li 		$t4, 0 			#inner loop couter j
cp_inner_loop:
	#j<N
	blt 	$t4, $s0, cp_inner_loop_end
	
	mul 	$t5, $t3, $s0	 #$t5 = N*i
	add 	$t5, $t5, $t4	 #$t5 = N*i+j
	
	#board[i][j] = newBoard[i][j]
	lb 		$t1, board($t5)			
	sb 		$t1, newBoard($t5)

cp_if:
	beq 	$t1, $0, dote
	bne 	$t1, $0, hash

dote:
	li 		$a0, '.'
	li 		$v0, 11
	syscall 	
	j 		cp_if_end	

hash:
	li 		$a0, '#'
	li 		$v0, 11
	syscall
	j 		cp_if_end

cp_if_end:
	addi 	$t4, $t4, 1 				#j++
	j 		cp_inner_loop  				#jump to begin

cp_inner_loop_end:
	addi 	$t3, $t3, 1					#i++
	li 		$a0, '\n'
	li 		$v0, 11
	syscall
	j 		cp_outer_loop

cp_outer_loop_end:
	j 		main_loop1_end


##void cp()
#copyBackAndShow:

#	li 		$t3, 0 			#outer for loop couter i

#cp_outer_loop:
#	# i<N
#	blt 	$t3, $s0, cp_outer_loop_end
#	li 		$t4, 0 			#inner loop couter j
#cp_inner_loop:
#	#j<N
#	blt 	$t4, $s0, cp_inner_loop_end
#	
#	mul 	$t5, $t3, $s0	 #$t5 = N*i
#	add 	$t5, $t5, $t4	 #$t5 = N*i+j
#	
#	#board[i][j] = newBoard[i][j]
#	lb 		$t1, board($t5)			
#	sb 		$t1, newBoard($t5)

#cp_if:
#	beq 	$t1, $0, dote
#	bne 	$t1, $0, hash

#dote:
#	li 		$a0, '.'
#	li 		$v0, 11
#	syscall 	
#	j 		cp_if_end	

#hash:
#	li 		$a0, '#'
#	li 		$v0, 11
#	syscall
#	j 		cp_if_end

#cp_if_end:
#	addi 	$t4, $t4, 1 				#j++
#	j 		cp_inner_loop  				#jump to begin

#cp_inner_loop_end:
#	addi 	$t3, $t3, 1					#i++
#	li 		$a0, '\n'
#	li 		$v0, 11
#	syscall
#	j 		cp_outer_loop

#cp_outer_loop_end:
#	jr   $ra 		#not sure void if needed return



#https://www.cs.colorado.edu/~kena/classes/5448/f12/presentation-materials/li.pdf
