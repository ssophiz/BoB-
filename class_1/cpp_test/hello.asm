global _start ; 레이블선언

section .text ; 지시지 밑은 텍스트
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, message
	mov rdx, 14
	syscall
	mov rax, 60
	xor rdi, rdi
	syscall
	
section .data ; 데이터 영역
message: db "Hello, World!", 10
