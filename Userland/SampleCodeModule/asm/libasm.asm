GLOBAL current_regs
GLOBAL test
GLOBAL invalidOp
section .text

invalidOp:
mov rax, 1
mov cr6, rax
ret
