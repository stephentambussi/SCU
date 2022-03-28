g:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$g.size, %esp
	movl	$0, %eax
	movl	%eax, 0+-4(%ebp)
.L0:
	movl	-4(%ebp), %eax
	cmpl	$10, %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L1
	leal	0+a, %eax
	movl	-4(%ebp), %ecx
	imull	$4, %ecx
	addl	%ecx, %eax
	movl	$0, %ecx
	movl	%ecx, 0(%eax)
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 0+-4(%ebp)
	jmp	.L0
.L1:

g.exit:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	g.size, 4
	.globl	g

	.comm	a, 40
