    global my_index

section .text
my_index:

	push	rdx
	xor		rax, rax

my_index_check_0:

	mov		dl, byte[rdi + rax]
	test	dl, dl
	jz		my_index_end_not_found

my_index_check_cmp_chr:

	cmp		dl, sil
	je		my_index_end_found
    inc     rax
    jmp     my_index_check_0
		
my_index_end_not_found:

	xor		rax, rax
	jmp		my_index_end

my_index_end_found:

	add		rax, rdi
    
my_index_end:

	pop		rdx
    ret