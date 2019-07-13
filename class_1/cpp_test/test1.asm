global _start

section .text
_start: 
	push rbp
	mov rbp, rsp
	
	mov rsp, rbp
	ret
