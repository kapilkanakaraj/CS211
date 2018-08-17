	.file	"mystery.c"
	.text
	.globl	add
	.type	add, @function
add:
.LFB35:
	.cfi_startproc
	leal	(%rdi,%rsi), %eax
	ret
	.cfi_endproc
.LFE35:
	.size	add, .-add
	.globl	formula
	.type	formula, @function
formula:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	%edi, %ebx
	movslq	%edi, %rax
	cmpl	$-1, numberArray(,%rax,4)
	jne	.L3
	testl	%edi, %edi
	jne	.L4
	movl	$0, numberArray(%rip)
	jmp	.L3
.L4:
	cmpl	$1, %edi
	jne	.L5
	movl	$1, numberArray+4(%rip)
	jmp	.L3
.L5:
	leal	-1(%rdi), %edi
	call	formula
	movl	%eax, %ebp
	leal	-2(%rbx), %edi
	call	formula
	movslq	%ebx, %rdx
	addl	%eax, %ebp
	movl	%ebp, numberArray(,%rdx,4)
.L3:
	movslq	%ebx, %rbx
	movl	numberArray(,%rbx,4), %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE36:
	.size	formula, .-formula
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Value:\t%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB37:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movl	$numberArray, %edx
	movl	$numberArray+1000, %ecx
.L9:
	movl	$-1, (%rdx)
	addq	$4, %rdx
	cmpq	%rcx, %rdx
	jne	.L9
	movl	%eax, %edi
	call	formula
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE37:
	.size	main, .-main
	.comm	numberArray,1000,32
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"
	.section	.note.GNU-stack,"",@progbits
