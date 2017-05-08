;Ross Bearden	
;CSCI 3130
;OLA 1
;1/28/2016

global main
extern printString

segment .text
	
main:
		;calling c function to print haiku
		mov rdi, message
		mov rsi, message1
		mov rdx, message2
		mov rcx, author
		call printString
		
		;exit(0)
		mov rax, 60
		mov rdi, 0
		syscall
		
		
segment .data
	message		db		"I want to sleep", 0         ;first line
	message1       db		"Swat the flies", 0		;second line
	message2	db		"Softly, please", 0		;thrid line
	author		db		"Masaoka Shiki", 0		
	
	
