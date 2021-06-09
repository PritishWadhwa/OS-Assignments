    global      _start:
    section     .text

_start:
    mov rdi,    101
	mov rsi,    20
	call        checkGreater

    global      checkGreater:
    section     .text 

checkGreater: 
    cmp rsi,    rdi
    jl          smaller
    jmp         larger
 
smaller: 
    mov rdi,    1 
	mov rax,    1 	
	mov rsi,    msg2 
	mov rdx,    msglen2
	syscall 
	mov rax,    60 
	mov rdi,    0 
	syscall 

larger:
    mov rdi,    1 
	mov rax,    1 
	mov rsi,    msg1
	mov rdx,    msglen1 
    syscall
	mov rax,    60 
	mov rdi,    0 
	syscall

    section     .rodata 
    msg1:       db      "0",    10 
	msglen1:    equ     $ - msg1
	msg2:       db      "1",    10 
	msglen2:    equ     $ - msg2

; global _start:
; section .text

; _start:
; 	mov rdi, 101
; 	mov rsi, 20
; 	call checkGreater

; global checkGreater:
; section .text 

; checkGreater: 
;     cmp rsi,rdi
; 	jl smaller
; 	jmp larger
 
; smaller: mov rdi, 1 
; 	mov rax, 1 	
; 	mov rsi, msg2 
; 	mov rdx, msglen2
; 	syscall 
; 	mov rax, 60 
; 	mov rdi, 0 
; 	syscall 

; larger: mov rdi, 1 
; 	mov rax, 1 
; 	mov rsi, msg1
; 	mov rdx, msglen1 
; 	syscall
; 	mov rax, 60 
; 	mov rdi, 0 
; 	syscall

; section .rodata 
; 	msg1: db "0", 10 
; 	msglen1: equ $ - msg1
; 	msg2: db "1", 10 
; 	msglen2: equ $ - msg2