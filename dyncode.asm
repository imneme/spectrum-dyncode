
	SECTION code_compiler
	GLOBAL _dyncode_full_romcall
	GLOBAL _dyncode_romcall
	GLOBAL _dyncode_preserve_ix
	GLOBAL _dyncode_quick
	GLOBAL _exit_msg
	GLOBAL _find_sp_for_basic

_exit_msg:
	ld	sp, ($5C3D)
	pop	bc
	push 	de
	ld      hl,$0000 	; prepare to clear some system variables.
	ld      ($5c0b),hl 	; blank DEFADD to signal that no defined
	ld      (iy+$26),l 	; blank X_PTR_hi to suppress error marker.
	ld      (iy+$37),l 	; clear all the bits of FLAGX.
				;  function is currently being evaluated.
	inc	hl		; set to $0001
	ld      ($5c16),hl 	; ensure STRMS-00 is keyboard.
	
	CALL    $16B0		; routine SET-MIN clears workspace etc.
	CALL    $0D6E		; call routine CLS-LOWER.

	set     5,(iy+$02) 	; update TV_FLAG - signal lower screen
				; requires clearing.
	pop	hl
print_loop:
	ld	a, (hl)
	or	a
	jr	z, done_print
	rst	$10
	inc	hl
	jr 	print_loop
done_print:	
	XOR	A
	ld	($5c3a), a
	jp	$1349

_sp_for_basic:
	defw	0


SYSVAR_RAMTOP           equ     $5CB2

_find_sp_for_basic:
;;; on entry, carry is clear
	ld	hl, (SYSVAR_RAMTOP)
	sbc	hl, sp
	jr	nc, sp_under_ramtop
find_loop:
	ld	a, (hl)
	dec	hl
	cp	$5c
	jr	nz, find_loop
	ld	a, (hl)
	dec	hl
	cp	$3a
	jr	nz, find_loop
	dec	hl
	ld	(_sp_for_basic), hl
	ret
sp_under_ramtop:
	ld	hl, sp
	ret
	
	
_dyncode_full_romcall:
	ld	hl, 2
	add	hl, sp
	push 	iy
	push	ix
	ld	(restore_stack+1), sp
	ex	de, hl
	ld	hl, (_sp_for_basic)
´	ld	a, h
	or	l
	call	z, _find_sp_for_basic
	ld	sp, hl
	ex	de, hl
	exx
	pop 	hl
	pop 	iy
	push	iy
	push	hl
	exx
	ld	de, dfr_nextbit
	push	de
	jp	(hl)
dfr_nextbit:
restore_stack:
	ld	sp, 0
	pop	ix
	pop	iy
	ret

_dyncode_romcall:
	ld	hl, 2
	add	hl, sp
	push 	iy
	push	ix
	ld      iy, $5c3a
	exx			
	ld	hl, $2758
	exx
	ld	de, nextbit
	push	de
	jp	(hl)
nextbit:
	pop	ix
	pop	iy
	ret

_dyncode_preserve_ix:
	ld	hl, 2
	add	hl, sp
	push	ix
	ld	de, continue
	push	de
	jp	(hl)
continue:
	pop	ix
	ret

_dyncode_quick:
	ld	hl, 2
	add	hl, sp
	jp	(hl)
