	SECTION data_compiler

_sp_for_basic:
	defw	0

	SECTION code_compiler
	GLOBAL _dyncode_zx_romcall_stdstack
	GLOBAL _zx_romcall_stdstack
	GLOBAL _find_sp_for_basic
	GLOBAL _jump_hl

SYSVAR_RAMTOP           equ     $5CB2

;;; _dyncode_zx_romcall_stdstack runs arbitary code that has been
;;; pushed onto the stack, falling through into _zx_romcall_stdstack
;;; (described below) which does the heavy lifting.
;;;
;;; On entry:   stack has: .... code .... start, return addr <- TOS
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers

_dyncode_zx_romcall_stdstack:
	ld	hl, 2			; load HL to stack beyond retaddr
	add	hl, sp			; this is where the dynamic code is
	;; fall through

;;; _zx_romcall_stdstack runs code pointed to by HL, preserving the caller's
;;; IX and IY. The code is run with IY and HL' as they were when the program
;;; was started, and also with the stack in its normal below-RAMTOP position,
;;; as various ROM routines would expect.  This is the surest way to call into
;;; the ROM if you do not expect errors via RST 8, or are happy for those
;;; errors to terminate the program.
;;;
;;; On entry:   HL = Routine to call
;;; 		BC,BC',DE',AF' = (Optionally) any arguments to the call.
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers
;;;
;;; Note:	The code you call cannot expect to find its arguments on the
;;;             stack, because the stack has moved. Stack restoration is
;;; 		via self-modifying code.

_zx_romcall_stdstack:
	push 	iy 			; save ix and iy
	push	ix
	ld	(restore_stack+1), sp	; modify later code to restore stack 
	ex	de, hl			; stash routine-to-call in DE for now
	ld	hl, (_sp_for_basic)	; swizzle the stack to the below-
´	ld	a, h			;   RAMTOP one, if we don't know where
	or	l			;   that is, figure it out
	call	z, _find_sp_for_basic   ;
	ld	sp, hl			; install new stack pointer
	ex	de, hl			; recover routine-to-call back to HL
	exx				; time to set regs to make ROM happy
	pop 	hl			;   HL' and IY were stored by CRT code
	pop 	iy			;   on this stack, so we grab their
	push	iy			;   values while leaving them in place
	push	hl			;
	exx				; that done, switch back from alt regs
	call	_jump_hl		; call the routine we're supposed to
restore_stack:
	ld	sp, 0 			; correct SP value via self-mod
	pop	ix			; restore caller's ix and iy
	pop	iy
	ret

;;; _find_sp_for_basic attempts to determine the correct stack-pointer to use
;;; to call BASIC routines that might expect it to be in the normal position.
;;;
;;; On entry:   carry must be clear
;;; On exit:    HL=Correct pointer value, also written to _sp_for_basic for
;;;             the future.
;;;             Smashed: A
;;; 		
;;; Note: 	The task would be trivial if the library exported
;;;       	__sp_or_ret, but since it doesn't, we have to get creative
;;;             and search for where it pushed IY to find the right value.
_find_sp_for_basic:
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
