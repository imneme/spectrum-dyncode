
	SECTION code_compiler
	GLOBAL _dyncode_preserve_ix
	GLOBAL _jump_hl

_dyncode_preserve_ix:
	ld	hl, 2
	add	hl, sp
	push	ix
	call	_jump_hl
	pop	ix
	ret

