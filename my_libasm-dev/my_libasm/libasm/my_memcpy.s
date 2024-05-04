    global my_memcpy

section .text
my_memcpy:
    test    rdx, rdx
    jz	    my_memcpy_end

    push    rcx
    push    rdx
    
    mov     rcx, rdx
    xor     rax, rax

my_memcpy_cpy:
    mov	    dl, byte[rsi + rax]
    mov	    byte[rdi + rax], dl
    inc	    rax
    loop    my_memcpy_cpy

    pop     rdx
    pop     rcx

my_memcpy_end:
    mov	    rax, rdi
    ret
