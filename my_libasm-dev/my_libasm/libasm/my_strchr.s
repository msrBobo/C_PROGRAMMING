    global my_strchr

section .text
my_strchr:
	push	rdx
	xor		rax, rax

my_strchr_check_0:
	mov		dl, byte[rdi + rax]
	test	dl, dl
	jz		my_strchr_end_not_found

my_strchr_check_cmp_chr:
	cmp		dl, sil
	je		my_strchr_end_found
    inc     rax
    jmp     my_strchr_check_0
	
my_strchr_end_not_found:
	xor		rax, rax
	jmp		my_strchr_end

my_strchr_end_found:
	add		rax, rdi
my_strchr_end:
	pop		rdx
    ret