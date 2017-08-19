#int x = 3;
#int y = 4;
	.data
x: 	.word 3
y:	.word 4
eol:.asciiz "\n"

	.text

main:
	lw $t0,x
	lw $t1,y
	add $a0, $t1, $t0 #reg[a0] = reg[t0]+reg[t1]
	li $v0,1
	syscall #print the result of 3+4 
    la $a0,eol
	li $v0,4
	syscall #printf(%s\n)
	jr $ra #return from main

