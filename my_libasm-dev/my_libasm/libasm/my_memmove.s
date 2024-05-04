    global my_memmove

section .text
my_memmove:
    test    dx, dx
    jz      my_memmove_only_ret

    sub     rsp, rdx

my_memmove_cpy:    
    push    rcx
    push    rbx
    
    mov     rcx, rdx
    xor     rax, rax
my_memmove_cpy_cpy1:    
    mov	    bl, byte[rsi + rax]
    mov	    byte[rsp + rax], bl
    inc	    rax
    loop    my_memmove_cpy_cpy1


    mov     rcx, rdx
    xor     rax, rax
my_memmove_cpy_cpy2:    
    mov	    bl, byte[rsp + rax]
    mov	    byte[rdi + rax], bl
    inc	    rax
    loop    my_memmove_cpy_cpy2

    pop     rbx
    pop     rcx

my_memmove_end:
    mov	    rax, rdi

my_memmove_ret:
    add     rsp, rdx

my_memmove_only_ret:
    ret