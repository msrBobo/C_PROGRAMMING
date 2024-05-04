    global my_strcasecmp

section .text
my_strcasecmp:
    push    rcx
    xor     rcx, rcx

my_strcasecmp_get:
    mov     al, byte[rdi + rcx]
    mov     ah, byte[rsi + rcx]

    test    al, al
    jnz     my_strcasecmp_do_sub
    test    ah, ah
    jnz     my_strcasecmp_do_sub

my_strcasecmp_both_zero:
    jmp     my_strcasecmp_end

my_strcasecmp_do_sub:
    call    my_strcasecmp_to_lower_al
    call    my_strcasecmp_to_lower_ah

    sub	    al, ah
    jne     my_strcasecmp_end
    inc     rcx
    jmp     my_strcasecmp_get

my_strcasecmp_end:
    movsx	rax, al
    pop     rcx
    ret

my_strcasecmp_to_lower_al:
    cmp     al, byte 'Z'
    jg      my_strcasecmp_to_lower_al_end
    cmp     al, byte 'A'
    jl      my_strcasecmp_to_lower_al_end
    add     al, byte 'a' - 'A'

my_strcasecmp_to_lower_al_end:
    ret

my_strcasecmp_to_lower_ah:
    cmp     ah, byte 'Z'
    jg      my_strcasecmp_to_lower_ah_end
    cmp     ah, byte 'A'
    jl      my_strcasecmp_to_lower_ah_end
    add     ah, byte 'a' - 'A'

my_strcasecmp_to_lower_ah_end:
    ret
