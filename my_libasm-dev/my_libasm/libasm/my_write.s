    global my_write

section .text
my_write:
    mov     rax, 1      ; "write"
    syscall
my_write_end:
    ret
