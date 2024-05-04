    global my_read

section .text
my_read:
    xor     rax, rax    ; "read"
    syscall
my_read_end:
    ret
