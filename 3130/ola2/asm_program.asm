;Ross Bearden
;CSCI 3130
;2/4/2016
;OLA2

global main
extern printf

segment .text

main:
	;Initialize loop
	mov rbx, 0

loop:
	cmp rbx, 9
	je done
	call newValues
	call calculate
	call printData
	jmp loop
	
calculate:
	mov rax, r8			;move first value to rax and do calculations from there
	sub  rax, r9
	mov r15, r10
	sub  r15, r11
	add  rax, r15
	ret	
	
printData:
	;Moving all values used in calculation into regeister
	;Last value contains the answer
	mov rdi, output
	mov rsi, r8
	mov rdx, r9
	mov rcx, r10
	mov r8, r11
	mov r9, rax
	mov al, 0
	call printf
	ret
	
newValues:
	;Obtaining values using offsets and the counter
	mov r8, [numarray+8*rbx]
	add rbx, 1
	mov r9, [numarray+8*rbx]
	add rbx, 1
	mov r10,[numarray+8*rbx]
	add rbx, 1
	mov r11,[numarray+8*rbx]
	;call print_equ
	sub rbx, 2
	ret
		
done:
	;exit (0)
	mov rax, 60
	mov rdi, 0
	syscall
	
	
	
segment .data
	numarray		dq	5, 10, 25, 100, 17, 30, 82, 70, 92, 6, 13, 55	
	output		db	"(%ld - %ld) + (%ld - %ld) = %ld", 10, 0