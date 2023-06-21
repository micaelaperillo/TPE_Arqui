
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _swInterruptHandler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

EXTERN getStackBase
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN swInterruptDispatcher
EXTERN displayRegs

SECTION .text

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

%macro pushStateInverse 0
    push rsp
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rsi
	push rdi
	push rbp
	push rdx
	push rcx
	push rbx
	push rax
%endmacro

%macro popStateInverse 0
	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rbp
	pop rdi
	pop rsi
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15
	pop rsp
%endmacro

%macro irqHandlerMaster 1
	pushStateInverse
	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp
	call irqDispatcher
	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	popStateInverse
	iretq
%endmacro



%macro exceptionHandler 1
    pushStateInverse
    mov rdi, rsp
    call displayRegs ; the registers need to be displayed asap
	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher
	popStateInverse
	call getStackBase
    sub rax, 20h
    mov qword [rsp+8*3], rax
	mov qword [rsp],400000h ;posicion del samplecodeModule
	iretq
%endmacro


;Software Interruption Handler
_swInterruptHandler:
    pushState
    call swInterruptDispatcher

    popState
    iretq

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	    0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0
_exception6Handler:; Invalid Operation Excepttion
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1
	registers resq 17
