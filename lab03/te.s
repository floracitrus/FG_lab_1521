	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	L_.str.2(%rip), %rdi
	leaq	L_.str(%rip), %rax
	leaq	L_.str.1(%rip), %rcx
	movq	%rcx, %rdx
	subq	%rax, %rdx
	movl	%edx, %esi
	movl	$0, -4(%rbp)
	movq	%rax, -16(%rbp)
	movq	%rcx, -24(%rbp)
	movq	-16(%rbp), %rcx
	subq	%rax, %rcx
	movl	%ecx, %r8d
	movl	%r8d, -28(%rbp)
	movl	%esi, -32(%rbp)
	movq	-24(%rbp), %rcx
	subq	%rax, %rcx
	movl	%ecx, %esi
	movl	%esi, -36(%rbp)
	movl	-28(%rbp), %esi
	movl	-32(%rbp), %edx
	movl	-36(%rbp), %ecx
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"0"

L_.str.1:                               ## @.str.1
	.asciz	"1"

L_.str.2:                               ## @.str.2
	.asciz	"%d, %d, %d "


.subsections_via_symbols
