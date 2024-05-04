global my_strlen

section .text
my_strlen:
    push    rcx
    xor     rcx, rcx
    xor     rax, rax

my_strlen_next:
    mov     al, byte[rdi]
    test    al, al
    je      my_strlen_null

    inc     rcx
    inc     rdi
    jmp     my_strlen_next

my_strlen_null:
    mov     rax, rcx
    pop     rcx
    ret