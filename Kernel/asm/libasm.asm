GLOBAL cpuVendor
GLOBAL keydown

section .text

keydown:
	push rbp
	mov rbp, rsp
.loop:
	in al, 64h
	and al, 0x01
	jz .loop
	in al, 60h
	leave
	ret
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
