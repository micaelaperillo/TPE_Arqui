GLOBAL getrsp
GLOBAL invalidOp
section .text

invalidOp:
mov rax, 1
mov cr6, rax
ret

getrsp:
mov rax, rsp
ret