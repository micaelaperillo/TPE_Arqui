GLOBAL getrsp
GLOBAL invalidOp
section .text

invalidOp:
mov cr6, rax
ret

getrsp:
mov rax, rsp
ret