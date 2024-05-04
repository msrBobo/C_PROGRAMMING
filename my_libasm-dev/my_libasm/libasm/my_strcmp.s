    global my_strcmp

section .text
my_strcmp:
    push    rcx
    xor     rcx, rcx

my_strcmp_get:
    mov     al, byte[rdi + rcx]
    mov     ah, byte[rsi + rcx]

    test    al, al
    jnz     my_strcmp_do_sub
    test    ah, ah
    jnz     my_strcmp_do_sub

my_strcmp_both_zero:
    jmp     my_strcmp_end

my_strcmp_do_sub:
    sub	    al, ah
    jne     my_strcmp_end
    inc     rcx
    jmp     my_strcmp_get

my_strcmp_end:
    movsx	rax, al
    pop     rcx
    ret