	.data
return_stack_top:		/* глубина текущего вызова, начиная от start */
	.long return_stack
	.bss
return_stack:			/* стек с адресами возврата */
	.space 4 * 0x1000


/* ----------------------------------------------------------- */
	
	.globl super_secure_call, super_secure_return
	.text

super_secure_call:
	mov (%esp), %eax
	mov 4(%esp), %ebx
	
	mov %ebx, (%esp)
	movl $0xdeadbeef, 4(%esp)

	mov return_stack_top, %edi
	mov %eax, (%edi)
	add $4, %edi
	mov %edi, return_stack_top

	ret

super_secure_return:
	add $4, %esp
	mov (%esp), %eax
	mov return_stack_top, %ebx
	sub $4, %ebx
	mov %ebx, return_stack_top
	mov (%ebx), %ebx

	mov %ebp, %esp
	pop %ebp

	push %ebx
	ret
	