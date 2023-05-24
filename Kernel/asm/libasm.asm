GLOBAL cpuVendor
GLOBAL keydown
GLOBAL interrupt
GLOBAL clock

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

clock:
	push rbp
	mov rbp, rsp

	mov al, dil 
	out 70h, al
	xor rax, rax
	in al, 71h
		
	mov rsp, rbp
	pop rbp
	ret

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

interrupt:
    pushstate
    int 80h
    popstate
    ret