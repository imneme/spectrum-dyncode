#ifndef ZX_ROMCALL_H_INCLUDED
#define ZXN_RPM3CALL_H_INCLUDED 1

extern void zx_exit_msg(char* message, short code);

#include <dyncode.h>

/* The p3call "continuation functions" also work for rom3call, as the
 * same registers are returned.
 */

#define ZX_ROM_PRINT_A_1  0x0010    // print char to current stream

#define zx_rom_print_a_1(c)					    \
    ((char*) dyncode_zx_romcall_stdstack(			    \
	DYNCODE_LOAD_A(c),					    \
	DYNCODE_RST_10,						    \
        DYNCODE_DONE						    \
    ))

#define ZX_ROM_BC_SPACES  0x0030    // allocate workspace

/* call with either
 * zx_rom_bc_spaces(size, SKIP)        to just return the start
 * zx_rom_bc_spaces(size, INTO(var))   to store the end pointer, too
 *                                     (INTO automagically takes the address
 *                                     of the var).
 */

#define zx_rom_bc_spaces(size, OPTOUT_endptr)				\
    ((char*) dyncode_zx_romcall_stdstack(				\
	DYNCODE_LOAD_BC__, DYNCODE___(size),				\
	DYNCODE_RST_30,							\
	DYNCODE_OPT_STORE_HL(OPTOUT_endptr)				\
	DYNCODE_SWAP_DE_HL,						\
        DYNCODE_DONE							\
	))

#define ZX_ROM_BEEPER     0x03b5    // make a sound using the beeper

#define zx_rom_beeper(freqtime, tstates)				\
    ((void) dyncode_zx_romcall(						\
	DYNCODE_LOAD_DE__, DYNCODE___(freqtime),			\
	DYNCODE_LOAD_HL__, DYNCODE___(tstates),				\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_BEEPER)			\
	))

#define ZX_ROM_SV_BYTES   0x04c2    // save bytes to tape

#define zx_rom_sv_bytes(type, start, length)				\
    ((void) dyncode_zx_romcall(						\
	DYNCODE_LOAD_A(type),						\
	DYNCODE_LOAD_IX__, DYNCODE___(start),				\
	DYNCODE_LOAD_DE__, DYNCODE___(length),				\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_SV_BYTES)			\
	))

#define ZX_ROM_LD_BYTES   0x0556    // load/verify bytes from tape

#define zx_rom_ld_bytes(type, loadNotVerify, start, length)		\
    ((short) dyncode_zx_romcall(					\
	DYNCODE_LOAD_A(type),						\
	DYNCODE_LOAD_IX__, DYNCODE___(start),				\
	DYNCODE_LOAD_DE__, DYNCODE___(length),				\
	(loadNotVerify ? DYNCODE_SET_C : DYNCODE_SET_Z) |		\
	DYNCODE_CALL__, DYNCODE___(ZX_ROM_LD_BYTES)			\
	DYNCODE_LOAD_HL__, DYNCODE___(0),				\
	DYNCODE_RET_NC |						\
        DYNCODE_DEC_HL,						       	\
	DYNCODE_DONE							\
	))

#define ZX_ROM_CLS        0x0d6b    // CLS

#define zx_rom_cls()							\
    ((void) zx_romcall_stdstack(ZX_ROM_CLS))

#define ZX_ROM_CLS_LOWER  0x0d6e    // Clear input area

#define zx_rom_cls_lower()						\
    ((void) zx_romcall_stdstack(ZX_ROM_CLS_LOWER))

#define ZX_ROM_EDITOR     0x0f2c    // main line-editor loop

#define zx_rom_editor(err)						\
    ((short) dyncode_zx_romcall_stdstack_err(				\
	err,								\
	DYNCODE_CALL__, DYNCODE___(ZX_ROM_EDITOR),			\
	DYNCODE_LOAD_HL__, DYNCODE___(0),				\
	DYNCODE_DONE							\
	))

#define ZX_ROM_WAIT_KEY   0x15d4    // wait for input on current input

#define zx_rom_wait_key()						\
    ((char) dyncode_zx_romcall(						\
        DYNCODE_CALL__, DYNCODE___(ZX_ROM_WAIT_KEY),			\
	DYNCODE_LOAD_L_A,						\
	DYNCODE_LOAD_H(0),						\
	DYNCODE_DONE							\
        ))

#define ZX_ROM_WAIT_KEY1  0x15de    // wait for input on current input

#define zx_rom_wait_key1()						\
    ((char) dyncode_zx_romcall(						\
        DYNCODE_CALL__, DYNCODE___(ZX_ROM_WAIT_KEY1),			\
	DYNCODE_LOAD_L_A,						\
	DYNCODE_LOAD_H(0),						\
	DYNCODE_DONE							\
        ))

#define ZX_ROM_PRINT_A_2  0x15f2    // print char to current stream

#define ZX_ROM_CALL_SUB   0x15f7    // execute routine at (HL') (trashes DE')

#define ZX_ROM_CHAN_OPEN  0x1601    // make stream in A current

#define zx_rom_chan_open(streamid)					\
    ((void) dyncode_zx_romcall(						\
	DYNCODE_LOAD_A(streamid),					\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_CHAN_OPEN)			\
	))

#define ZX_ROM_CALL_JUMP  0x162c    // execute routine at HL

#define ZX_ROM_SET_MIN    0x16b0    // reset editing area (and SET_WORK)

#define zx_rom_set_min()						\
    ((void) dyncode_zx_romcall_stdstack(				\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_SET_MIN)			\
        ))

#define ZX_ROM_SET_WORK   0x16bf    // zap the work space (and SET_STK)

#define zx_rom_set_work()						\
    ((void) dyncode_zx_romcall_stdstack(				\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_SET_WORK)			\
        ))

#define ZX_ROM_SET_STK    0x16c5    // reset calculator stack

#define zx_rom_set_stk()						\
    ((void) dyncode_zx_romcall_stdstack(				\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_SET_STK)			\
        ))

#define ZX_ROM_CLASS_01   0x1c1f    // determine the address of a variable

#define ZX_ROM_OUT_SP_NO  0x192a    // print a digit helper (E=' ' or $FF)

#define ZX_ROM_RECLAIM_1  0x19e5    // reclaim [DE..HL)

#define zx_rom_reclaim_1(start,end)					\
    ((void*) dyncode_zx_romcall(					\
	DYNCODE_LOAD_DE__, DYNCODE___(start),				\
	DYNCODE_LOAD_HL__, DYNCODE___(end),				\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_RECLAIM_1)			\
	))

#define ZX_ROM_RECLAIM_2  0x19e8    // reclaim BC bytes at HL

#define zx_rom_reclaim_2(start,length)				\
    ((void*) dyncode_zx_romcall(					\
	DYNCODE_LOAD_HL__, DYNCODE___(start),				\
	DYNCODE_LOAD_BC__, DYNCODE___(length),				\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_RECLAIM_2)			\
	))

#define ZX_ROM_OUT_NUM_1  0x1a1B    // print a num (<9999) from BC, (E=...)

#define zx_rom_out_num_1(num,space)					\
    ((void*) dyncode_zx_romcall(                                        \
        DYNCODE_LOAD_BC__, DYNCODE___(num),				\
        DYNCODE_LOAD_E(space),						\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_OUT_NUM_3)                  \
	))

#define ZX_ROM_SP_NO	    0x192a

#define zx_rom_out_num_16bit(num,space)				\
    ((void*) dyncode_zx_romcall(                                        \
        DYNCODE_LOAD_HL__, DYNCODE___(num),				\
        DYNCODE_LOAD_E(space),						\
	DYNCODE_LOAD_BC__, DYNCODE___(0xd8f0)				\
	DYNCODE_CALL__, DYNCODE___(ZX_ROM_SP_NO)			\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_OUT_NUM_3)                  \
	))

#define ZX_ROM_TEST_ROOM  0x1f05    // check for free mem in basic workspace

#define zx_rom_test_room(space)						\
    ((unsigned short) dyncode_zx_romcall_stdstack(			\
        DYNCODE_LOAD_BC__, DYNCODE___(space),				\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_TEST_ROOM)			\
        ))

#define ZX_ROM_PAUSE_1    0x1f3d    // interuptable pause for BC frames

#define zx_rom_pause_1(frames)					\
    ((unsigned short) dyncode_zx_romcall(				\
	DYNCODE_LOAD_BC__, DYNCODE___(frames),				\
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_PAUSE_1)			\
        ))

#define ZX_ROM_PR_STRING  0x203c    // print string (DE = string, BC = count)

#define zx_rom_pr_string(addr,length)					\
    ((void) dyncode_zx_romcall_stdstack(				\
	DYNCODE_LOAD_DE__, DYNCODE___(addr),				\
	DYNCODE_LOAD_BC__, DYNCODE___(length),				\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_PR_STRING)			\
	))

#define ZX_ROM_PLOT_SUB   0x22e5    // plot a point

#define zx_rom_plot_sub(x,y)						\
    ((void) dyncode_zx_romcall(						\
	DYNCODE_LOAD_B(y),						\
	DYNCODE_LOAD_C(x),						\
	DYNCODE_JUMP__, DYNCODE___(ZX_ROM_PLOT_SUB)			\
	))

#define ZX_ROM_STK_STO_S  0x2ab2    // store string on calc stack

#define ZX_ROM_LET        0x2aff    // LET

#define ZX_ROM_PRINT_FP   0x2de3    // print floating point from calc stack

#define ZX_ROM_STACK_A    0x2d28    // push A to calculator stack


#endif /* ZX_ROMCALL_H_INCLUDED */
