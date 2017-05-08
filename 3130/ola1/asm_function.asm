;Ross Bearden	
;CSCI 3130
;OLA 1
;1/28/2016

global asm_function

segment .text

asm_function:
		;using write
		mov rax, 1			;write command
		mov rdx, rsi			;move length to rdx
		mov rsi, rdi			;move message to rsi
		mov rdi, 1			;stdout
		syscall				;calling os
		ret					;returning to c program
		