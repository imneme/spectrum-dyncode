#ifndef DYNCODE_H_INCLUDED
#define DYNCODE_H_INCLUDED 1

#ifdef __SDCC
#define __stdc
#endif

short dyncode_zx_romcall(unsigned short magic, ...) __stdc;
short dyncode_zx_romcall_stdstack(unsigned short magic, ...) __stdc;
short dyncode_zx_romcall_stdstack_err(short (*handler)(void), ...) __stdc;
short zx_romcall(unsigned short) __stdc __z88dk_fastcall;
short zx_romcall_stdstack(unsigned short) __stdc __z88dk_fastcall;
short zx_romcall_stdstack_err(short (*handler)(void), unsigned short) 
    __stdc __z88dk_callee __stdc;

#define DYNCODE_DONE	     	0x00c9

#define DYNCODE_NOP             0x0000
#define DYNCODE_CRASH           0x76f3

#define DYNCODE_SET_C           0x3700
#define DYNCODE_SET_Z           0xbf00

#define DYNCODE_LOAD_A(n)       ((((char) (n)) << 8) | 0x3e)
#define DYNCODE_LOAD_B(n)       ((((char) (n)) << 8) | 0x06)
#define DYNCODE_LOAD_C(n)       ((((char) (n)) << 8) | 0x0e)
#define DYNCODE_LOAD_D(n)       ((((char) (n)) << 8) | 0x16)
#define DYNCODE_LOAD_E(n)       ((((char) (n)) << 8) | 0x1e)
#define DYNCODE_LOAD_H(n)       ((((char) (n)) << 8) | 0x26)
#define DYNCODE_LOAD_L(n)       ((((char) (n)) << 8) | 0x2e)

#define DYNCODE_SWAP_DE_HL      0xeb00

#define DYNCODE_LOAD_A_B        0x7800
#define DYNCODE_LOAD_A_C        0x7900
#define DYNCODE_LOAD_A_D        0x7a00
#define DYNCODE_LOAD_A_E        0x7b00
#define DYNCODE_LOAD_A_H        0x7c00
#define DYNCODE_LOAD_A_I        0x57ed
#define DYNCODE_LOAD_A_L        0x7d00
#define DYNCODE_LOAD_A_R        0x5fed
#define DYNCODE_LOAD_B_A        0x4700
#define DYNCODE_LOAD_B_C        0x4100
#define DYNCODE_LOAD_B_D        0x4200
#define DYNCODE_LOAD_B_E        0x4300
#define DYNCODE_LOAD_B_H        0x4400
#define DYNCODE_LOAD_B_L        0x4500
#define DYNCODE_LOAD_C_A        0x4f00
#define DYNCODE_LOAD_C_B        0x4800
#define DYNCODE_LOAD_C_D        0x4a00
#define DYNCODE_LOAD_C_E        0x4b00
#define DYNCODE_LOAD_BC_DE      0x4b42
#define DYNCODE_LOAD_C_H        0x4c00
#define DYNCODE_LOAD_C_L        0x4d00
#define DYNCODE_LOAD_BC_HL      0x4d44
#define DYNCODE_LOAD_D_A        0x5700
#define DYNCODE_LOAD_D_B        0x5000
#define DYNCODE_LOAD_D_C        0x5100
#define DYNCODE_LOAD_D_E        0x5300
#define DYNCODE_LOAD_D_H        0x5400
#define DYNCODE_LOAD_D_L        0x5500
#define DYNCODE_LOAD_E_A        0x5f00
#define DYNCODE_LOAD_E_B        0x5800
#define DYNCODE_LOAD_E_C        0x5900
#define DYNCODE_LOAD_E_D        0x5a00
#define DYNCODE_LOAD_E_H        0x5c00
#define DYNCODE_LOAD_E_L        0x5d00
#define DYNCODE_LOAD_H_A        0x6700
#define DYNCODE_LOAD_H_B        0x6000
#define DYNCODE_LOAD_H_C        0x6100
#define DYNCODE_LOAD_H_D        0x6200
#define DYNCODE_LOAD_H_E        0x6300
#define DYNCODE_LOAD_H_L        0x6500
#define DYNCODE_LOAD_I_A        0x47ed
#define DYNCODE_LOAD_L_A        0x6f00
#define DYNCODE_LOAD_L_B        0x6800
#define DYNCODE_LOAD_L_C        0x6900
#define DYNCODE_LOAD_L_D        0x6a00
#define DYNCODE_LOAD_L_E        0x6b00
#define DYNCODE_LOAD_L_H        0x6c00
#define DYNCODE_LOAD_R_A        0x4fed
#define DYNCODE_LOAD_IXH_A      0x67dd
#define DYNCODE_LOAD_IXH_B      0x60dd
#define DYNCODE_LOAD_IXH_C      0x61dd
#define DYNCODE_LOAD_IXH_D      0x62dd
#define DYNCODE_LOAD_IXH_E      0x63dd
#define DYNCODE_LOAD_IYH_A      0x67fd
#define DYNCODE_LOAD_IYH_B      0x60fd
#define DYNCODE_LOAD_IYH_C      0x61fd
#define DYNCODE_LOAD_IYH_D      0x62fd
#define DYNCODE_LOAD_IYH_E      0x63fd
#define DYNCODE_LOAD_IXL_A      0x6fdd
#define DYNCODE_LOAD_IXL_B      0x68dd
#define DYNCODE_LOAD_IXL_C      0x69dd
#define DYNCODE_LOAD_IXL_D      0x6add
#define DYNCODE_LOAD_IXL_E      0x6bdd
#define DYNCODE_LOAD_IYL_A      0x6ffd
#define DYNCODE_LOAD_IYL_B      0x68fd
#define DYNCODE_LOAD_IYL_C      0x69fd
#define DYNCODE_LOAD_IYL_D      0x6afd
#define DYNCODE_LOAD_IYL_E      0x6bfd
#define DYNCODE_LOAD_A_IXH      0x7cdd
#define DYNCODE_LOAD_A_IYH      0x7cfd
#define DYNCODE_LOAD_A_IXL      0x7ddd
#define DYNCODE_LOAD_A_IYL      0x7dfd
#define DYNCODE_LOAD_B_IXH      0x44dd
#define DYNCODE_LOAD_B_IYH      0x44fd
#define DYNCODE_LOAD_B_IXL      0x45dd
#define DYNCODE_LOAD_B_IYL      0x45fd
#define DYNCODE_LOAD_C_IXH      0x4cdd
#define DYNCODE_LOAD_C_IYH      0x4cfd
#define DYNCODE_LOAD_C_IXL      0x4ddd
#define DYNCODE_LOAD_C_IYL      0x4dfd
#define DYNCODE_LOAD_D_IXH      0x54dd
#define DYNCODE_LOAD_D_IYH      0x54fd
#define DYNCODE_LOAD_D_IXL      0x55dd
#define DYNCODE_LOAD_D_IYL      0x55fd
#define DYNCODE_LOAD_E_IXH      0x5cdd
#define DYNCODE_LOAD_E_IYH      0x5cfd
#define DYNCODE_LOAD_E_IXL      0x5ddd
#define DYNCODE_LOAD_E_IYL      0x5dfd

#define DYNCODE___(word)        ((unsigned short) (word))

#define DYNCODE_LOAD_BC__       0x0100
#define DYNCODE_LOAD_DE__       0x1100
#define DYNCODE_LOAD_HL__       0x2100
#define DYNCODE_LOAD_IX__       0x21dd
#define DYNCODE_LOAD_IY__       0x21fd
#define DYNCODE_LOAD_SP__       0x3100

#define DYNCODE_INDLOAD_A__     0x3a00
#define DYNCODE_INDLOAD_BC__    0x4bed
#define DYNCODE_INDLOAD_DE__    0x5bed
#define DYNCODE_INDLOAD_HL__    0x2a00
// #define DYNCODE_INDLOAD_HL__    0x6bed
#define DYNCODE_INDLOAD_IX__    0x2add
#define DYNCODE_INDLOAD_IY__    0x2afd
#define DYNCODE_INDLOAD_SP__    0x7bed

#define DYNCODE_STORE_A__       0x3200
#define DYNCODE_STOREviaA_0__   0x32af
#define DYNCODE_STOREviaA_B__   0x3278
#define DYNCODE_STOREviaA_C__   0x3279
#define DYNCODE_STOREviaA_D__   0x327a
#define DYNCODE_STOREviaA_E__   0x327b
#define DYNCODE_STOREviaA_H__   0x327c
#define DYNCODE_STOREviaA_L__   0x327d

#define DYNCODE_STORE_BC__      0x43ed
#define DYNCODE_STORE_DE__      0x53ed
#define DYNCODE_STORE_HL__      0x2200
// #define DYNCODE_STORE_HL__      0x63ed
#define DYNCODE_STORE_IX__      0x22dd
#define DYNCODE_STORE_IY__      0x22fd
#define DYNCODE_STORE_SP__      0x73ed

#define DYNCODE_OPT_STORE_A(optaddr)        DYNCODE_STORE_A_ ## optaddr
#define DYNCODE_STORE_A_SKIP
#define DYNCODE_STORE_A_INTO(var)           DYNCODE_STORE_A__, DYNCODE___(&var),

#define DYNCODE_OPT_STOREviaA_B(optaddr)    DYNCODE_STOREviaA_B_ ## optaddr
#define DYNCODE_STOREviaA_B_SKIP
#define DYNCODE_STOREviaA_B_INTO(var)       DYNCODE_STOREviaA_B__, DYNCODE___(&var),

#define DYNCODE_OPT_STOREviaA_C(optaddr)    DYNCODE_STOREviaA_C_ ## optaddr
#define DYNCODE_STOREviaA_C_SKIP
#define DYNCODE_STOREviaA_C_INTO(var)       DYNCODE_STOREviaA_C__, DYNCODE___(&var),

#define DYNCODE_OPT_STOREviaA_D(optaddr)    DYNCODE_STOREviaA_D_ ## optaddr
#define DYNCODE_STOREviaA_D_SKIP
#define DYNCODE_STOREviaA_D_INTO(var)       DYNCODE_STOREviaA_D__, DYNCODE___(&var),

#define DYNCODE_OPT_STOREviaA_E(optaddr)    DYNCODE_STOREviaA_E_ ## optaddr
#define DYNCODE_STOREviaA_E_SKIP
#define DYNCODE_STOREviaA_E_INTO(var)       DYNCODE_STOREviaA_E__, DYNCODE___(&var),

#define DYNCODE_OPT_STOREviaA_H(optaddr)    DYNCODE_STOREviaA_H_ ## optaddr
#define DYNCODE_STOREviaA_H_SKIP
#define DYNCODE_STOREviaA_H_INTO(var)       DYNCODE_STOREviaA_H__, DYNCODE___(&var),

#define DYNCODE_OPT_STOREviaA_L(optaddr)    DYNCODE_STOREviaA_L_ ## optaddr
#define DYNCODE_STOREviaA_L_SKIP
#define DYNCODE_STOREviaA_L_INTO(var)       DYNCODE_STOREviaA_L__, DYNCODE___(&var),

#define DYNCODE_OPT_STORE_BC(optaddr)       DYNCODE_STORE_BC_ ## optaddr
#define DYNCODE_STORE_BC_SKIP
#define DYNCODE_STORE_BC_INTO(var)          DYNCODE_STORE_BC__, DYNCODE___(&var),

#define DYNCODE_OPT_STORE_DE(optaddr)       DYNCODE_STORE_DE_ ## optaddr
#define DYNCODE_STORE_DE_SKIP
#define DYNCODE_STORE_DE_INTO(var)          DYNCODE_STORE_DE__, DYNCODE___(&var),

#define DYNCODE_OPT_STORE_HL(optaddr)       DYNCODE_STORE_HL_ ## optaddr
#define DYNCODE_STORE_HL_SKIP
#define DYNCODE_STORE_HL_INTO(var)          DYNCODE_STORE_HL__, DYNCODE___(&var),

#define DYNCODE_OPT_STORE_IX(optaddr)       DYNCODE_STORE_IX_ ## optaddr
#define DYNCODE_STORE_IX_SKIP
#define DYNCODE_STORE_IX_INTO(var)          DYNCODE_STORE_IX__, DYNCODE___(&var),

#define DYNCODE_X2_OPTIONAL_STORE(dynop, addr) \
    (addr) ? dynop : DYNCODE_NOP,	    \
	(addr) ? DYNCODE___(addr) : DYNCODE_NOP	


#define DYNCODE_ALT_ALL         0x08d9
#define DYNCODE_ALT_AF          0x0800
#define DYNCODE_ALT_BCDEHL      0xd900

#define DYNCODE_PUSH_AF         0xf500
#define DYNCODE_PUSH_BC         0xc500
#define DYNCODE_PUSH_AFBC       0xc5f5
#define DYNCODE_PUSH_DE         0xd500
#define DYNCODE_PUSH_HL         0xe500
#define DYNCODE_PUSH_DEHL       0xe5d5
#define DYNCODE_PUSH_IX         0xe5dd
#define DYNCODE_PUSH_IY         0xe5fd
#define DYNCODE_PUSH_LIT__be    0x8aed, (((n & 0xff) << 8)|((n & 0xff00) >> 8))
					// Spectrum Next Only

#define DYNCODE_POP_AF          0xf100
#define DYNCODE_POP_BC          0xc100
#define DYNCODE_POP_BCAF        0xf1c1
#define DYNCODE_POP_DE          0xd100
#define DYNCODE_POP_HL          0xe100
#define DYNCODE_POP_HLDE        0xd1e1
#define DYNCODE_POP_IX          0xe1dd
#define DYNCODE_POP_IY          0xe1fd

#define DYNCODE_RELJMP(dops)    ((((char) dops) << 9) | 0x18)
#define DYNCODE_RELJMP_NC(dops) ((((char) dops) << 9) | 0x30)
#define DYNCODE_RELJMP_C(dops)  ((((char) dops) << 9) | 0x38)
#define DYNCODE_RELJMP_NZ(dops) ((((char) dops) << 9) | 0x20)
#define DYNCODE_RELJMP_Z(dops)  ((((char) dops) << 9) | 0x28)

#define DYNCODE_CALL__          0xcd00
#define DYNCODE_CALL_C__        0xdc00
#define DYNCODE_CALL_M__        0xfc00
#define DYNCODE_CALL_NC__       0xd400
#define DYNCODE_CALL_NZ__       0xc400
#define DYNCODE_CALL_P__        0xf400
#define DYNCODE_CALL_PO__       0xe400
#define DYNCODE_CALL_PE__       0xec00
#define DYNCODE_CALL_Z__        0xcc00

#define DYNCODE_JUMP_HL         0xe900
#define DYNCODE_JUMP_IX         0xe9dd
#define DYNCODE_JUMP_IY         0xe9fd
#define DYNCODE_JUMP_IOIN_BC    0x98ed
#define DYNCODE_JUMP__          0xc300
#define DYNCODE_JUMP_C__        0xda00
#define DYNCODE_JUMP_M__        0xfa00
#define DYNCODE_JUMP_NC__       0xd200
#define DYNCODE_JUMP_NZ__       0xc200
#define DYNCODE_JUMP_P__        0xf200
#define DYNCODE_JUMP_PO__       0xe200
#define DYNCODE_JUMP_PE__       0xea00
#define DYNCODE_JUMP_Z__        0xca00

#define DYNCODE_RST_00	        0xc700
#define DYNCODE_RST_08(defb)	((((char) defb) << 8) | 0xcf)
#define DYNCODE_RST_10          0xd700
#define DYNCODE_RST_18__	0xdf00
#define DYNCODE_RST_20	        0xe700
#define DYNCODE_RST_28(defb)	((((char) defb) << 8) | 0xef)
#define DYNCODE_RST_30   	0xf700
#define DYNCODE_RST_38	        0xff00

#endif // DYNCODE_H_INCLUDED
