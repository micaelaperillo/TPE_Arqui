GLOBAL cpuVendor
GLOBAL keydown
GLOBAL interrupt
GLOBAL clock
GLOBAL play_sound
GLOBAL stop_sound
GLOBAL timer_wait
GLOBAL current_regs

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

play_sound:
	; code adapted from https://wiki.osdev.org/PC_Speaker
    push rbp
    mov rbp, rsp
    push rbx
    push rdx

    mov ah, 2
    mov dl, 7
    int 21h

    mov al, 0xB6
    out 0x43, al

    mov ebx, edi
    mov al, byte [ebx]
    out 0x42, al

    shr ebx, 8
    mov al, byte [ebx]
    out 0x42, al

    in al, 0x61
    mov bl, al

    or bl, 3
    cmp al, bl
    je .finish

    mov al, bl
    out 0x61, al

.finish:
    pop rdx
    pop rbx
    mov rsp, rbp
    pop rbp
    ret

stop_sound:
    push rbp
    mov rbp, rsp

    in al, 0x61
    and al, 0xFC
    out 0x61, al

    mov rsp, rbp
    pop rbp
    ret

timer_wait:
    push rbp
    mov rbp, rsp

    mov eax, dword [rbp+16]    ; recibe el tiempo que espera
    mov ebx, eax              	

    ; calcula numero de ciclos que tiene que esperar
    mov ecx, 0                	
    mov edx, 1000000          
    mul edx                   
    mov ecx, eax              
    xor edx, edx              
    mov eax, ebx              
    mul edx                   
    add eax, ecx              
	
wait_loop:
    rdtsc                     
    cmp rax, rdx              
    jb wait_loop              

    pop rbp
    ret

current_regs:
	; gets current registers
	mov [registers], rax
	mov [registers+8], rax
	mov [registers+8*2], rax
	mov [registers+8*3], rax
	mov [registers+8*4], rax
	mov [registers+8*5], rax
	mov [registers+8*6], rax
	mov [registers+8*7], rax
	mov [registers+8*8], rax
	mov [registers+8*9], rax
	mov [registers+8*10], rax
	mov [registers+8*11], rax
	mov [registers+8*12], rax
	mov [registers+8*13], rax
	mov [registers+8*14], rax
	mov rax, registers
	ret

section .bss:
	registers resb 8 * 18