.globl nCr
	.type	nCr, @function
nCr:
  .LFB0:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        pushq   %r12
        pushq   %rbx
        subq    $16, %rsp
        .cfi_offset 12, -24
        .cfi_offset 3, -32
        movl    %edi, -20(%rbp)
        movl    %esi, -24(%rbp)
        movl    -20(%rbp), %eax
        movl    %eax, %edi
        movl    $0, %eax
        call    factorial
        movl    %eax, %ebx
        movl    -24(%rbp), %eax
        movl    %eax, %edi
        movl    $0, %eax
        call    factorial
        movl    %eax, %r12d
        movl    -24(%rbp), %eax
        movl    -20(%rbp), %edx
        subl    %eax, %edx
        movl    %edx, %eax
        movl    %eax, %edi
        movl    $0, %eax
        call    factorial
        movl    %r12d, %edx
        imull   %eax, %edx
        movl    %edx, %ecx
        movl    %ebx, %eax
        cltd
        idivl   %ecx
        addq    $16, %rsp
        popq    %rbx
        popq    %r12
        popq    %rbp
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc


.globl factorial
	.type	factorial, @function
factorial:
  .LFB1:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        movl    %edi, -20(%rbp)
        movl    $1, -4(%rbp)
        movl    $1, -8(%rbp)
        cmpl    $0, -20(%rbp)
        jne     .L2
        movl    -4(%rbp), %eax
        jmp     .L3
.L2:
        jmp     .L4
.L5:
        movl    -4(%rbp), %eax
        imull   -8(%rbp), %eax
        movl    %eax, -4(%rbp)
        addl    $1, -8(%rbp)
.L4:
        movl    -8(%rbp), %eax
        cmpl    -20(%rbp), %eax
        jle     .L5
        movl    -4(%rbp), %eax
.L3:
        popq    %rbp
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc
