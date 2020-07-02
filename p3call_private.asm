;;; This code was written by hand!

        SECTION data_compiler
	GLOBAL	_zxn_p3call_err
	GLOBAL  _zxn_private_callp3dos
	GLOBAL  _zxn_private_callp3dos_err
	
_zxn_p3call_err:
	defb	0

	SECTION code_compiler
	GLOBAL  zxn_p3cont_errcheck
	
;;; On entry, 
;;;     HL = Call-ID
;;; 	C  = HiMem Ram bank
;;;     IX = P3DOS IX
;;;     AF,BC',DE',HL' = Entry parameters
;;; On Exit
;;;     Registers exactly as per P3DOS docs (i.e., IX has correct value)

_zxn_private_callp3dos:
	ld	d, ixh		; Copy IX register into DE (to put in HL)
	ld	e, ixl		; ...
	ex	de, hl		; M_P3DOS wants call id in DE, and IX in HL
				; (only needed for dot cmd, but doesn't hurt)
IF 1
	rst	$08
	defb	$94		; M_P3DOS

	exx
ELSE
	scf
ENDIF
	ex	de, hl
	ld	ixh, d
	ld	ixl, e
	exx
	ret

_zxn_private_callp3dos_err:
	call	_zxn_private_callp3dos
	jr	nc, is_error
	ld	a, 0		; zero but do so *without* changing flags
	ld	(_zxn_p3call_err), a
	ret
is_error:
	pop	hl		; discard return address 
				; nothing else to pop
	ld	(_zxn_p3call_err), a ; store it
	ld	hl, $FFFF	; return -1
	ld	d, h		; even if it's a 32-bit return
	ld	e, l
	ret			; return to dyncode dispatcher
