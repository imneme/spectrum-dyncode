	SECTION data_compiler

	SECTION code_compiler
	GLOBAL _dyncode_zx_romcall_err
	GLOBAL _zx_romcall_err
	GLOBAL _zx_romcall
        GLOBAL _zx_romcall_private_restore_stack
	GLOBAL _call_with_errhandler

SYSVAR_ERR_SP           equ     $5C3D

;;; _zx_romcall_err is a standard calling conventions shim for
;;; _asm_zx_romcall_err
;;;
;;; On entry:   stack has: routine-to-call, handler, return addr <- TOS
;;; On exit:    IX,IY unchanged + (see _asm_zx_romcall_err)

_zx_romcall_err:
	pop	de			; return address
	pop	bc			; error handler
	pop	hl			; subroutine
	push	de			; restore return address
	jp	_asm_zx_romcall_err

;;; _dyncode_zx_romcall_err runs arbitary code that has been pushed
;;; onto the stack, falling through into asm_zx_romcall_err
;;; (described below), which does the heavy lifting.
;;;
;;; On entry:   stack has: .... code .... start, handler, return addr <- TOS
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers

_dyncode_zx_romcall_err:
	ld	hl, 2			; load HL to stack beyond retaddr
	add	hl, sp
	ld	c, (hl)			; copy error handler, and adjust
	inc	hl			; HL to be past that
	ld	b, (hl)
	inc	hl			; this is where the dynamic code is
	;; fall through

;;; _asm_zx_romcall_err runs code pointed to by HL with an error
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

_asm_zx_romcall_err:
	ex	de, hl
	exx
	ld	hl, _call_with_errhandler
	jp	_zx_romcall
