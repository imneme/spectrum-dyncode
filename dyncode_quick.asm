
	SECTION code_compiler
	GLOBAL _dyncode_quick

_dyncode_quick:
	ld	hl, 2
	add	hl, sp
	jp	(hl)
