f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$f.size, %esp
	movl	4+n, %eax
	movl	%eax, 12+-16(%ebp)

f.exit:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	f.size, 16
	.globl	f

	.comm	n, 16
