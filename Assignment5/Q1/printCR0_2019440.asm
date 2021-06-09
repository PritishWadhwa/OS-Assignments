;Name: Pritish Wadhwa
;Roll Number: 2019440

bits 16
org 0x7c00

boot:
	mov ax, 0x3
	int 0x10
	mov ax, 0x2401
	int 0x15
	mov eax, cr0
	or eax,0x1
	mov cr0, eax
	lgdt [gdt_pointer]
	jmp CODE:boot2

bits 32
boot2:
	mov ax, DATA
	mov esi,val
	mov ebx,0xb8000

.loop:
	or eax, 0x0F00 
	lodsb
	mov word [ebx], ax
	or al,al
	jz .print_cr0_contents
	add ebx,2
	jmp .loop

.print_cr0_contents:
    mov edx, cr0

.print_cr0_contents_loop:
    or edx, 0x0
    jz halt
	mov eax, edx   
    and eax, 0x1    
    add eax, 48     
    or eax, 0x0F00  
    mov word [ebx], ax
    add ebx, 2
    shr edx, 1
    jmp .print_cr0_contents_loop

gdt_start:
	dq 0x0

gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

gdt_end:

gdt_pointer:
	dw gdt_end - gdt_start
	dd gdt_start

halt:
	cli
	hlt

CODE equ gdt_code - gdt_start
DATA equ gdt_data - gdt_start

val: db "Value in CR0 Register in Big Endian: ",0

times 510 - ($-$$) db 0
dw 0xaa55