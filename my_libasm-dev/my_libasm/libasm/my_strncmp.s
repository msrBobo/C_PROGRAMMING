    global my_strncmp

section .text
my_strncmp:
    push    rcx
    xor     rcx, rcx


my_strncmp_get:
    cmp     rcx, rdx
    jz      my_strncmp_end_cnt0
    
    mov     al, byte[rdi + rcx]
    mov     ah, byte[rsi + rcx]

    test    al, al
    jnz     my_strncmp_do_sub
    test    ah, ah
    jnz     my_strncmp_do_sub

my_strncmp_both_zero:
    jmp     my_strncmp_end

my_strncmp_do_sub:
    sub	    al, ah
    jne     my_strncmp_end
    inc     rcx
    jmp     my_strncmp_get

my_strncmp_end_cnt0:
    xor     al, al
my_strncmp_end:
    movsx	rax, al
    pop     rcx
    ret