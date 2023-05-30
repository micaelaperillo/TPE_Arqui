GLOBAL current_regs
GLOBAL test
GLOBAL invalidOp
section .text
invalidOp:
mov cr6, rax
ret
current_regs:
	; gets current registers, this function is a duplicate from current_regs in the kernel
	; this is because when getting the regiter values through a system call, they are modified in the call itself
	mov [registers], rax
	mov [registers+8], rbx
	mov [registers+8*2], rcx
	mov [registers+8*3], rdx
	mov [registers+8*4], rsi
	mov [registers+8*5], rdi
	mov [registers+8*6], rbp
	mov [registers+8*7], r8
	mov [registers+8*8], r9
	mov [registers+8*9], r10
	mov [registers+8*10], r11
	mov [registers+8*11], r12
	mov [registers+8*12], r13
	mov [registers+8*13], r14
	mov [registers+8*14], r15
	mov [registers+8*15], rsp
	mov rax, [rsp]
	mov [registers+8*16], rax
	mov rax, registers
	ret

section .bss
	registers resb 8 * 17
