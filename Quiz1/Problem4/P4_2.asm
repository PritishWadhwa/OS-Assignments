    global  extended_add
    section .text
extended_add:
    mov     rax, rdi
    add     rax, rsi
    add     rax, rdx
    add     rax, rcx
    ret