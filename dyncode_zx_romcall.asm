
	SECTION code_compiler
	GLOBAL _dyncode_zx_romcall
	GLOBAL _zx_romcall
	GLOBAL _jump_hl

;;; _dyncode_zx_romcall runs arbitary code that has been pushed onto
;;; the stack, falling through into _zx_romcall (described below)
;;; which does the heavy lifting.
;;;
;;; On entry:   stack has: .... code .... start, return addr <- TOS
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers

_dyncode_zx_romcall:
	ld	hl, 2			; load HL to stack beyond retaddr
	add	hl, sp			; this is where the dynamic code is
	;; fall through
	
;;; _zx_romcall runs code pointed to by HL, perserving the caller's IX and IY.
;;; The code is run with IY set to its standard value.  It does NOT set HL';
;;; if you need a sane value of HL' for a ROM routine, use the _alt version
;;; which sets it to $2758, a "usually good enough" one.  This is often a
;;; completely adequate way to call a reasonably self-contained routine, but
;;; not one that errors out and tries to return to BASIC, because HL' is not
;;; set, and the stack is in the wrong place, above RAMTOP.
;;;
;;; On entry:   HL = Routine to call
;;; 		AF,BC,DE,BC',DE',HL',AF' = (Optionally) any args to the call.
;;; On exit:    IX,IY unchanged + whatever the routine leaves in the registers
;;;
;;; Note:	The code you call cannot expect to find its arguments on the
;;;             stack, because things will have been pushed onto the stack.

_zx_romcall:
	push 	iy
	push	ix
	ld      iy, $5c3a
	call	_jump_hl
	pop	ix
	pop	iy
	ret
