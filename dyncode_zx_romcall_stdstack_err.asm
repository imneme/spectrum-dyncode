	SECTION data_compiler

	SECTION code_compiler
	GLOBAL _dyncode_zx_romcall_stdstack_err
	GLOBAL _zx_romcall_stdstack_err
	GLOBAL _zx_romcall_stdstack
        GLOBAL _zx_romcall_private_restore_stack

SYSVAR_ERR_SP           equ     $5C3D

;;; _zx_romcall_stdstack_err is a standard calling conventions shim for
;;; _asm_zx_romcall_stdstack_err
;;;
;;; On entry:   stack has: routine-to-call, handler, return addr <- TOS
;;; On exit:    IX,IY unchanged + (see _asm_zx_romcall_stdstack_err)

_zx_romcall_stdstack_err:
	pop	de			; return address
	pop	bc			; error handler
	pop	hl			; subroutine
	push	de			; restore return address
	jp	_asm_zx_romcall_stdstack_err

;;; _dyncode_zx_romcall_stdstack_err runs arbitary code that has been pushed
;;; onto the stack, falling through into asm_zx_romcall_stdstack_err
;;; (described below), which does the heavy lifting.
;;;
;;; On entry:   stack has: .... code .... start, handler, return addr <- TOS
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers

_dyncode_zx_romcall_stdstack_err:
	ld	hl, 2			; load HL to stack beyond retaddr
	add	hl, sp
	ld	c, (hl)			; copy error handler, and adjust
	inc	hl			; HL to be past that
	ld	b, (hl)
	inc	hl			; this is where the dynamic code is
	;; fall through

;;; _asm_zx_romcall_stdstack_err runs code pointed to by HL with an error
;;; handling routine in BC. It preserves the caller's IX and IY, and calls
;;; the ROM with IY and HL' as they were when the program was started.  The
;;; code is run with the stack in its normal below-RAMTOP position, as various
;;; ROM routines would expect.  This is the surest way to call into the ROM,
;;; especially if there is a chance of an error via RST 8.
;;;
;;; On entry:   HL = Routine to call
;;; 		BC = Error handler routine
;;; 		BC',AF' = (Optionally) any arguments to the call, BC' will be
;;; 		          in BC a the time of the call.
;;; On exit:    IX,IY unchanged + BC trashed + whatever the routine leaves
;;; 		in the registers
;;;
;;; Note:	The code you call cannot expect to find its arguments on the
;;;             stack, because the stack has moved. Stack restoration is
;;; 		via self-modifying code.

_asm_zx_romcall_stdstack_err:
	ex	de, hl
	exx
	ld	hl, call_with_errhandler
	jp	_zx_romcall_stdstack

;;; On entry:	DE'=Routine to call, BC'=Error Hander
;;; On exit:	(whatever *either* the routine to call, *OR* the error handler
;;; 		returns EXCEPT FOR BC, which is trashed -- generally we expect
;;; 		results to be in HL or DEHL)
call_with_errhandler:
	ld	hl, (SYSVAR_ERR_SP)	; save the old error handler
	push	hl			;
	ld	hl, restore_err_sp	; when we return from error handler,
	push	hl			; exit via restore_err_sp which will
					; restore it
	exx				; access our arguments
	push	bc			; push the error handler
	ld	(SYSVAR_ERR_SP), sp	; install it
	call 	jump_de_alt		; call de after switching regs
	pop	bc			; discard our (unused) error handler
	pop	bc			; and retaddr that would take us here
restore_err_sp:
	pop	bc			; retrieve old error handler
	ld	(SYSVAR_ERR_SP), bc	; install it
	ret

jump_de_alt:
	push	de			; where we're jumping to
	exx				; switch registers first
	ret				; whee, off we go
