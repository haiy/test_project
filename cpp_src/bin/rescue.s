	.file	"rescue.c"
	.text
	.p2align 4,,15
	.globl	push_node
	.type	push_node, @function
push_node:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$16, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	malloc
	movq	(%rbx), %rdx
	movq	$0, 8(%rax)
	movl	%ebp, (%rax)
	testq	%rdx, %rdx
	je	.L6
	movq	%rdx, 8(%rax)
	movq	%rax, (%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	.cfi_restore_state
	movq	%rax, (%rbx)
	movq	%rax, 8(%rbx)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	push_node, .-push_node
	.p2align 4,,15
	.globl	pop_node
	.type	pop_node, @function
pop_node:
.LFB24:
	.cfi_startproc
	movq	(%rdi), %rdx
	testq	%rdx, %rdx
	je	.L9
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	8(%rdx), %rax
	movl	(%rdx), %ebx
	movq	%rax, (%rdi)
	movq	%rdx, %rdi
	call	free
	movl	%ebx, %eax
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	movl	$-1, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	pop_node, .-pop_node
	.p2align 4,,15
	.globl	prime_check
	.type	prime_check, @function
prime_check:
.LFB25:
	.cfi_startproc
	leal	-2(%rdi), %eax
	cmpl	$1, %eax
	jbe	.L17
	movl	%edi, %esi
	shrl	$31, %esi
	addl	%edi, %esi
	sarl	%esi
	cmpl	$1, %esi
	jle	.L17
	movl	%edi, %eax
	shrl	$31, %eax
	leal	(%rdi,%rax), %edx
	andl	$1, %edx
	subl	%eax, %edx
	testl	%edx, %edx
	je	.L13
	movl	$2, %ecx
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L15:
	movl	%edi, %eax
	cltd
	idivl	%ecx
	testl	%edx, %edx
	je	.L13
.L14:
	addl	$1, %ecx
	cmpl	%esi, %ecx
	jle	.L15
.L17:
	movl	$1, %edx
.L13:
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE25:
	.size	prime_check, .-prime_check
	.p2align 4,,15
	.globl	find_MIN
	.type	find_MIN, @function
find_MIN:
.LFB26:
	.cfi_startproc
	imull	%ecx, %edx
	testl	%edx, %edx
	jle	.L28
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	movl	$2147483647, %r9d
	.p2align 4,,10
	.p2align 3
.L27:
	movl	(%rdi,%rcx,4), %r8d
	cmpl	%r9d, %r8d
	jg	.L26
	cmpl	$-1, (%rsi,%rcx,4)
	cmovne	%ecx, %eax
	cmovne	%r8d, %r9d
.L26:
	addq	$1, %rcx
	cmpl	%ecx, %edx
	jg	.L27
	rep ret
.L28:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE26:
	.size	find_MIN, .-find_MIN
	.p2align 4,,15
	.globl	dst_cal
	.type	dst_cal, @function
dst_cal:
.LFB27:
	.cfi_startproc
	movl	%edi, %eax
	cltd
	idivl	%ecx
	movl	%eax, %r8d
	movl	%esi, %eax
	movl	%edx, %r9d
	cltd
	idivl	%ecx
	cmpl	%eax, %r8d
	je	.L38
	subl	%eax, %r8d
	movl	%r8d, %ecx
	movl	%r8d, %eax
	sarl	$31, %ecx
	xorl	%ecx, %eax
	subl	%ecx, %eax
	cmpl	$1, %eax
	je	.L39
.L33:
	movl	$2147483647, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L38:
	movl	%edi, %eax
	subl	%esi, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L33
.L32:
	rep ret
	.p2align 4,,10
	.p2align 3
.L39:
	cmpl	%edx, %r9d
	je	.L32
	movl	$2147483647, %eax
	.p2align 4,,3
	ret
	.cfi_endproc
.LFE27:
	.size	dst_cal, .-dst_cal
	.p2align 4,,15
	.globl	print_map
	.type	print_map, @function
print_map:
.LFB28:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE28:
	.size	print_map, .-print_map
	.p2align 4,,15
	.globl	dijkstra
	.type	dijkstra, @function
dijkstra:
.LFB29:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movl	%ecx, %r13d
	imull	%r8d, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	leal	-1(%r13), %eax
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	cmpl	$1, %eax
	movq	%rsi, -16(%rsp)
	movl	%eax, -4(%rsp)
	jle	.L42
	movq	%rdx, %r12
	movl	$1, -8(%rsp)
	movl	%r8d, %ebp
	.p2align 4,,10
	.p2align 3
.L43:
	testl	%r13d, %r13d
	jle	.L66
	xorl	%eax, %eax
	xorl	%esi, %esi
	movl	$2147483647, %ecx
	.p2align 4,,10
	.p2align 3
.L59:
	movl	(%rdi,%rax,4), %edx
	cmpl	%ecx, %edx
	jg	.L44
	cmpl	$-1, (%r12,%rax,4)
	cmovne	%eax, %esi
	cmovne	%edx, %ecx
.L44:
	addq	$1, %rax
	cmpl	%eax, %r13d
	jg	.L59
	movslq	%esi, %rax
	salq	$2, %rax
	cmpl	%esi, 56(%rsp)
	movq	%rax, -32(%rsp)
	je	.L71
.L46:
	movq	-32(%rsp), %rax
	xorl	%ecx, %ecx
	testl	%r13d, %r13d
	movq	%rdi, %r11
	movl	%esi, %r10d
	movl	$-1, (%r12,%rax)
	jle	.L56
	.p2align 4,,10
	.p2align 3
.L67:
	cmpl	$-1, (%r12,%rcx,4)
	movl	%ecx, %r9d
	je	.L50
	movq	-32(%rsp), %rax
	movl	(%rdi,%rax), %r15d
	movl	%esi, %eax
	cltd
	idivl	%ebp
	movl	%eax, %ebx
	movl	%ecx, %eax
	movl	%edx, -20(%rsp)
	cltd
	idivl	%ebp
	cmpl	%eax, %ebx
	movl	%eax, %r14d
	je	.L72
	movl	%ebx, %r8d
	subl	%eax, %r8d
	movl	%r8d, %eax
	sarl	$31, %eax
	xorl	%eax, %r8d
	subl	%eax, %r8d
	cmpl	$1, %r8d
	je	.L73
	movl	$2147483647, %r8d
.L54:
	addl	%r15d, %r8d
	cmpl	(%r11), %r8d
	jge	.L50
	subl	%r14d, %ebx
	movl	%ebx, %eax
	sarl	$31, %eax
	xorl	%eax, %ebx
	subl	%eax, %ebx
	cmpl	$1, %ebx
	je	.L74
	.p2align 4,,10
	.p2align 3
.L50:
	addq	$1, %rcx
	addq	$4, %r11
	subl	$1, %r10d
	cmpl	%ecx, %r13d
	jg	.L67
.L56:
	addl	$1, -8(%rsp)
	movl	-4(%rsp), %eax
	cmpl	%eax, -8(%rsp)
	jne	.L43
.L42:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	movl	$-1, %eax
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L74:
	.cfi_restore_state
	movl	%esi, %eax
	cltd
	idivl	%ebp
	movl	%r9d, %eax
	movl	%edx, %r8d
	cltd
	idivl	%ebp
	cmpl	%edx, %r8d
	jne	.L50
	leal	1(%r15), %eax
.L60:
	movl	%eax, (%r11)
	movq	-16(%rsp), %rax
	movl	%esi, (%rax,%rcx,4)
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L72:
	movl	%r10d, %edx
	sarl	$31, %edx
	movl	%edx, %eax
	xorl	%r10d, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L50
	leal	1(%r15), %eax
	cmpl	(%r11), %eax
	jge	.L50
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L73:
	cmpl	%edx, -20(%rsp)
	movl	$2147483647, %eax
	cmovne	%eax, %r8d
	jmp	.L54
.L66:
	xorl	%esi, %esi
	cmpl	%esi, 56(%rsp)
	movq	$0, -32(%rsp)
	jne	.L46
.L71:
	movq	-16(%rsp), %rax
	movq	-32(%rsp), %rsi
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	movl	(%rax,%rsi), %eax
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE29:
	.size	dijkstra, .-dijkstra
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d%d"
.LC1:
	.string	"%d"
.LC2:
	.string	"What a pity!"
.LC3:
	.string	"(%d,%d)"
.LC4:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB30:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$.LC0, %edi
	xorl	%eax, %eax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	leaq	56(%rsp), %rdx
	leaq	52(%rsp), %rsi
	call	__isoc99_scanf
	movslq	56(%rsp), %rdx
	movslq	52(%rsp), %rax
	imulq	%rdx, %rax
	leaq	0(,%rax,4), %rdi
	call	malloc
	movl	52(%rsp), %ecx
	movl	56(%rsp), %r8d
	movq	%rax, %rbx
	xorl	%eax, %eax
	movl	%ecx, %edx
	imull	%r8d, %edx
	testl	%edx, %edx
	jle	.L79
	.p2align 4,,10
	.p2align 3
.L127:
	movl	$1, (%rbx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %edx
	jg	.L127
.L79:
	xorl	%ebp, %ebp
	testl	%ecx, %ecx
	jle	.L78
	.p2align 4,,10
	.p2align 3
.L132:
	testl	%r8d, %r8d
	jle	.L90
	xorl	%r14d, %r14d
	jmp	.L91
	.p2align 4,,10
	.p2align 3
.L140:
	movl	56(%rsp), %r8d
	movl	%ebp, %r12d
	imull	%r8d, %r12d
	addl	%r14d, %r12d
.L83:
	addl	$1, %r14d
	cmpl	%r8d, %r14d
	jge	.L90
.L91:
	leaq	60(%rsp), %rsi
	xorl	%eax, %eax
	movl	$.LC1, %edi
	call	__isoc99_scanf
	movl	60(%rsp), %esi
	testl	%esi, %esi
	je	.L140
	cmpl	$1, %esi
	je	.L141
	leal	-2(%rsi), %eax
	cmpl	$1, %eax
	jbe	.L85
	movl	%esi, %edi
	shrl	$31, %edi
	addl	%esi, %edi
	sarl	%edi
	cmpl	$1, %edi
	jle	.L85
	movl	%esi, %edx
	shrl	$31, %edx
	leal	(%rsi,%rdx), %eax
	andl	$1, %eax
	cmpl	%edx, %eax
	je	.L86
	movl	$2, %ecx
	jmp	.L87
	.p2align 4,,10
	.p2align 3
.L88:
	movl	%esi, %eax
	cltd
	idivl	%ecx
	testl	%edx, %edx
	je	.L86
.L87:
	addl	$1, %ecx
	cmpl	%edi, %ecx
	jle	.L88
.L85:
	movl	56(%rsp), %r8d
	movl	%ebp, %eax
	imull	%r8d, %eax
	addl	%r14d, %eax
	addl	$1, %r14d
	cltq
	cmpl	%r8d, %r14d
	movl	$-1, (%rbx,%rax,4)
	jl	.L91
.L90:
	addl	$1, %ebp
	cmpl	%ebp, 52(%rsp)
	jg	.L132
.L78:
	movslq	%r12d, %r15
	leaq	64(%rsp), %rdi
	movl	%r13d, %esi
	leaq	(%rbx,%r15,4), %rax
	movq	$0, 72(%rsp)
	movq	$0, 64(%rsp)
	movl	$-1, (%rax)
	movq	%rax, 16(%rsp)
	movslq	%r13d, %rax
	movl	$2147483647, (%rbx,%rax,4)
	call	push_node
	movslq	56(%rsp), %rdx
	movslq	52(%rsp), %rax
	imulq	%rdx, %rax
	leaq	0(,%rax,4), %rdi
	call	malloc
	movslq	56(%rsp), %rdx
	movq	%rax, %rbp
	movslq	52(%rsp), %rax
	imulq	%rdx, %rax
	leaq	0(,%rax,4), %rdi
	call	malloc
	movl	56(%rsp), %r8d
	movl	52(%rsp), %edi
	movq	%rax, %r14
	imull	%r8d, %edi
	testl	%edi, %edi
	jle	.L92
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L94:
	movl	$-1, (%r14,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %edi
	jg	.L94
	movq	16(%rsp), %rax
	movl	%r12d, (%r14,%r15,4)
	movq	%rbx, %r11
	movq	%r14, 24(%rsp)
	movl	%r12d, %r10d
	xorl	%ecx, %ecx
	movl	%r13d, 36(%rsp)
	movq	%rbx, 40(%rsp)
	movl	$0, (%rax)
	movq	%rax, %r14
	.p2align 4,,10
	.p2align 3
.L102:
	cmpl	$-1, 0(%rbp,%rcx,4)
	movl	%ecx, %r9d
	je	.L95
	movl	%r12d, %eax
	movl	(%r14), %r15d
	cltd
	idivl	%r8d
	movl	%eax, %ebx
	movl	%ecx, %eax
	movl	%edx, 16(%rsp)
	cltd
	idivl	%r8d
	cmpl	%eax, %ebx
	movl	%eax, %r13d
	je	.L142
	movl	%ebx, %esi
	subl	%eax, %esi
	movl	%esi, %eax
	sarl	$31, %eax
	xorl	%eax, %esi
	subl	%eax, %esi
	cmpl	$1, %esi
	je	.L143
	movl	$2147483647, %esi
.L99:
	addl	%r15d, %esi
	cmpl	(%r11), %esi
	jge	.L95
	subl	%r13d, %ebx
	movl	%ebx, %eax
	sarl	$31, %eax
	xorl	%eax, %ebx
	subl	%eax, %ebx
	cmpl	$1, %ebx
	je	.L144
.L95:
	addq	$1, %rcx
	addq	$4, %r11
	subl	$1, %r10d
	cmpl	%ecx, %edi
	jg	.L102
.L146:
	movl	36(%rsp), %r13d
	movq	40(%rsp), %rbx
	movq	24(%rsp), %r14
.L101:
	cmpl	%r13d, %r12d
	je	.L107
	.p2align 4,,10
	.p2align 3
.L104:
	movl	52(%rsp), %ecx
	movl	%ecx, %r15d
	imull	%r8d, %r15d
	testl	%r15d, %r15d
	jle	.L108
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L109:
	movl	(%rbx,%r10,4), %r11d
	movl	%r11d, 0(%rbp,%r10,4)
	addq	$1, %r10
	cmpl	%r10d, %r15d
	jg	.L109
.L108:
	movl	%r13d, (%rsp)
	movl	%r12d, %r9d
	movq	%rbp, %rdx
	movq	%r14, %rsi
	movq	%rbx, %rdi
	call	dijkstra
	cmpl	$-1, %eax
	movl	%eax, %r13d
	je	.L145
	leaq	64(%rsp), %rdi
	movl	%eax, %esi
	call	push_node
	cmpl	%r12d, %r13d
	je	.L107
	movl	56(%rsp), %r8d
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L141:
	movl	56(%rsp), %r8d
	movl	%ebp, %r13d
	imull	%r8d, %r13d
	addl	%r14d, %r13d
	jmp	.L83
	.p2align 4,,10
	.p2align 3
.L86:
	movl	56(%rsp), %r8d
	movl	%ebp, %eax
	imull	%r8d, %eax
	addl	%r14d, %eax
	cltq
	movl	$2147483647, (%rbx,%rax,4)
	jmp	.L83
.L144:
	movl	%r12d, %eax
	cltd
	idivl	%r8d
	movl	%r9d, %eax
	movl	%edx, %esi
	cltd
	idivl	%r8d
	cmpl	%edx, %esi
	jne	.L95
	addl	$1, %r15d
.L115:
	movq	24(%rsp), %rax
	movl	%r15d, (%r11)
	subl	$1, %r10d
	addq	$4, %r11
	movl	%r12d, (%rax,%rcx,4)
	addq	$1, %rcx
	cmpl	%ecx, %edi
	jg	.L102
	jmp	.L146
.L142:
	movl	%r10d, %edx
	sarl	$31, %edx
	movl	%edx, %eax
	xorl	%r10d, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L95
	addl	$1, %r15d
	cmpl	(%r11), %r15d
	jl	.L115
	jmp	.L95
	.p2align 4,,10
	.p2align 3
.L143:
	cmpl	%edx, 16(%rsp)
	movl	$2147483647, %eax
	cmovne	%eax, %esi
	jmp	.L99
.L145:
	movl	$.LC2, %edi
	call	puts
.L107:
	movq	64(%rsp), %r12
	xorl	%r13d, %r13d
	testq	%r12, %r12
	je	.L110
	.p2align 4,,10
	.p2align 3
.L112:
	movl	(%r12), %eax
	movl	$.LC3, %edi
	addl	$1, %r13d
	cltd
	idivl	56(%rsp)
	movl	%eax, %esi
	xorl	%eax, %eax
	call	printf
	movq	64(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L111
	movq	8(%rdi), %rax
	movq	%rax, 64(%rsp)
	call	free
.L111:
	movq	8(%r12), %r12
	testq	%r12, %r12
	jne	.L112
.L110:
	movq	%rbx, %rdi
	call	free
	movq	%rbp, %rdi
	call	free
	movl	$10, %edi
	call	putchar
	leal	-1(%r13), %esi
	movl	$.LC4, %edi
	xorl	%eax, %eax
	call	printf
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L92:
	.cfi_restore_state
	movq	16(%rsp), %rax
	movl	%r12d, (%r14,%r15,4)
	movl	$0, (%rax)
	jmp	.L101
	.cfi_endproc
.LFE30:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.1 20130603 (Red Hat 4.8.1-1)"
	.section	.note.GNU-stack,"",@progbits
