    global my_memset

section .text
my_memset:
    xor     rax, rax

my_memset_cmp_cnt:
    cmp     rax, rdx
    je      my_memset_end
    mov     byte[rdi + rax], sil
    inc     rax
    jmp     my_memset_cmp_cnt

my_memset_end:
    mov     rax, rdi
    ret
