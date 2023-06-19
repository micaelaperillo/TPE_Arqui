GLOBAL current_regs
GLOBAL test
GLOBAL invalidOp
section .text

invalidOp:
mov cr6, rax
ret
