
	SECTION code_compiler
	GLOBAL _zx_exit_msg_call
	GLOBAL _zx_exit_msg
	GLOBAL _zx_romcall_stdstack

SYSVAR_DEFADD           equ     $5C0B
SYSVAR_ERR_NR           equ     $5C3A
SYSVAR_ERR_SP           equ     $5C3D
	
ROM3_SET_MIN            equ     $16B0
ROM3_CLS_LOWER	        equ     $0D6E
	
_zx_exit_msg:
	pop	hl			; remove retaddr to get to args
	pop	bc			; string to print goes into BC
	pop	de			; value for ERR_NR
	ld	a,e
	ld	(SYSVAR_ERR_NR), a 	; write the value
	push	hl			; restore retaddr, although unlikely
					; it'll ever be used
	ld	hl, _zx_exit_msg_call
	jp	_zx_romcall_stdstack

_zx_exit_msg_call:
	ld	sp, (SYSVAR_ERR_SP) 	; assumes that the standard error
					; is in place (!!??!!)
	pop	hl			; throw away error handler
	push 	bc			; stash address of error string
	ld      hl,0 			; zero to clear some system variables.
	ld      (SYSVAR_DEFADD),hl 	; zero DEFADD (no current func)
	ld      (iy+$37),l 		; zero FLAGX.
	
	call    ROM3_SET_MIN		; clears workspace, calc stack, etc.
	call    ROM3_CLS_LOWER		; clear lower screen

	set     5,(iy+$02) 		; next key should clear lower screen

	pop	hl			; unstash error string address
print_loop:
	ld	a, (hl)			; it's a C-style string, ends with '\0'
	or	a
	jr	z, done_print
	rst	$10
	inc	hl
	jr 	print_loop
done_print:	
	ld	($5c3a), a
	jp	$1349

