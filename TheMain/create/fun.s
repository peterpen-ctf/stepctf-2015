.text
.globl _start, flag
_start:	
	xor    %ebp,%ebp
	pop    %esi
	mov    %esp,%ecx
	and    $0xfffffff0,%esp
	push   %eax
	push   %esp
	push   %edx
	push   $0x80484d0
	push   $0x8048460
	push   %ecx
	push   %esi
	push   $main
	call __libc_start_main
	push $lol
	call printf
	push $0
	call exit

__libc_start_main:
	push $solve
	call super_secure_call
	push %eax
	call exit

lol:	
	.string "Unbellieveable!\n"
