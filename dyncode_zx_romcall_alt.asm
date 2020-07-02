	SECTION code_compiler
	GLOBAL _dyncode_zx_romcall_alt
	GLOBAL _zx_romcall_alt

;;; _dyncode_zx_romcall_alt runs arbitary code that has been pushed onto
;;; the stack, falling through into _zx_romcall_alt (described below)
;;; which does the heavy lifting.
;;;
;;; On entry:   stack has: .... code .... start, return addr <- TOS
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers

_dyncode_zx_romcall_alt:
	ld	hl, 2			; load HL to stack beyond retaddr
	add	hl, sp			; this is where the dynamic code is
	;; fall through
	
;;; _zx_romcall_alt runs code pointed to by HL, perserving the caller's IX and
;;; IY.  The code is run with IY set to its standard value.  It also sets HL'
;;; to $2758, a "usually good enough" value.  This is often a completely
;;; adequate way to call a reasonably self-contained routine, but not one that
;;; errors out and tries to return to BASIC, because the stack is in the wrong
;;; place, above RAMTOP.
;;;
;;; On entry:   HL = Routine to call
;;; 		AF,BC,DE,BC',DE',AF' = (Optionally) any args to the call.
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers
;;;
;;; Note:	The code you call cannot expect to find its arguments on the
;;;             stack, because things will have been pushed onto the stack.

_zx_romcall_alt:
	exx
	ld	hl, $2758
	exx
	jp	_zx_romcall

