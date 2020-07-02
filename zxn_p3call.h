#ifndef ZXN_P3CALL_H_INCLUDED
#define ZXN_P3CALL_H_INCLUDED 1

#include "dyncode.h"

extern void zxn_private_callp3dos();
extern void zxn_private_callp3dos_err();
extern char zxn_p3call_err;

#define DYNCODE_ZXN_P3DOS_SETUP(callid, himem)	\
    ((DYNCODE_ALT_BCDEHL >> 8) | DYNCODE_LOAD_HL__), DYNCODE___(callid), \
	DYNCODE_LOAD_C(himem)		

#define DYNCODE_ZXN_P3DOS_CALL(details)			\
    DYNCODE_ZXN_P3DOS_SETUP(details),			\
	DYNCODE_CALL__, DYNCODE___(zxn_private_callp3dos)

#define DYNCODE_ZXN_P3DOS_CALL_ERR(details)		\
    DYNCODE_ZXN_P3DOS_SETUP(details),			\
	DYNCODE_CALL__, DYNCODE___(zxn_private_callp3dos_err)

#define DYNCODE_ZXN_P3DOS_JUMP(details)			\
    DYNCODE_ZXN_P3DOS_SETUP(details),			\
	DYNCODE_JUMP__, DYNCODE___(zxn_private_callp3dos)

#define DYNCODE_ZXN_P3DOS_JUMP_ERR(details)		\
    DYNCODE_ZXN_P3DOS_SETUP(details),			\
	DYNCODE_JUMP__, DYNCODE___(zxn_private_callp3dos_err)

/*
 * ZXN_DOS_VERSION (0x0103) [HiMem = 7]
 *    Get +3DOS issue and version numbers
 *
 * Inputs:  
 * Output:  D,E
 */
#define ZXN_DOS_VERSION            0x0103, 7

/*
 * ZXN_DOS_OPEN (0x0106) [HiMem = 7]
 *    Create and/or open a file
 *
 * Inputs:  B,C,D,E,HL
 * Output:     (and on failure A)
 */
#define ZXN_DOS_OPEN               0x0106, 7

/*
 * ZXN_DOS_CLOSE (0x0109) [HiMem = 7]
 *    Close a file
 *
 * Inputs:  B
 * Output:     (and on failure A)
 */
#define ZXN_DOS_CLOSE              0x0109, 7

/*
 * ZXN_DOS_ABANDON (0x010C) [HiMem = 7]
 *    Abandon a file
 *
 * Inputs:  B
 * Output:     (and on failure A)
 */
#define ZXN_DOS_ABANDON            0x010C, 7

/*
 * ZXN_DOS_REF_HEAD (0x010F) [HiMem = 7]
 *    Point at the header data for this file
 *
 * Inputs:  B
 * Output:     (and on failure A)
 */
#define ZXN_DOS_REF_HEAD           0x010F, 7

/*
 * ZXN_DOS_READ (0x0112) [HiMem = 7]
 *    Read bytes into memory
 *
 * Inputs:  B,C,DE,HL
 * Output:     (and on failure A,DE)
 */
#define ZXN_DOS_READ               0x0112, 7

/*
 * ZXN_DOS_WRITE (0x0115) [HiMem = 7]
 *    Write bytes from memory
 *
 * Inputs:  B,C,DE,HL
 * Output:     (and on failure A,DE)
 */
#define ZXN_DOS_WRITE              0x0115, 7

/*
 * ZXN_DOS_BYTE_READ (0x0118) [HiMem = 7]
 *    Read a byte
 *
 * Inputs:  B
 * Output:     (and on failure A)
 */
#define ZXN_DOS_BYTE_READ          0x0118, 7

/*
 * ZXN_DOS_BYTE_WRITE (0x011B) [HiMem = 7]
 *    Write a byte
 *
 * Inputs:  B,C
 * Output:     (and on failure A)
 */
#define ZXN_DOS_BYTE_WRITE         0x011B, 7

/*
 * ZXN_DOS_CATALOG (0x011E) [HiMem = 7]
 *    Catalog disk directory
 *
 * Inputs:  B,C,DE,HL
 * Output:     (and on failure A)
 */
#define ZXN_DOS_CATALOG            0x011E, 7

/*
 * ZXN_DOS_FREE_SPACE (0x0121) [HiMem = 7]
 *    Free space on disk
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_DOS_FREE_SPACE         0x0121, 7

/*
 * ZXN_DOS_DELETE (0x0124) [HiMem = 7]
 *    Delete a file
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DOS_DELETE             0x0124, 7

/*
 * ZXN_DOS_RENAME (0x0127) [HiMem = 7]
 *    Rename a file
 *
 * Inputs:  DE,HL
 * Output:     (and on failure A)
 */
#define ZXN_DOS_RENAME             0x0127, 7

/*
 * ZXN_DOS_BOOT (0x012A) [HiMem = 7]
 *    Boot an operating system or other program
 *
 * Inputs:  
 * Output:     (and on failure A)
 */
#define ZXN_DOS_BOOT               0x012A, 7

/*
 * ZXN_DOS_SET_DRIVE (0x012D) [HiMem = 7]
 *    Set/get default drive
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_DOS_SET_DRIVE          0x012D, 7

/*
 * ZXN_DOS_SET_USER (0x0130) [HiMem = 7]
 *    Set/get default user number
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_DOS_SET_USER           0x0130, 7

/*
 * ZXN_DOS_GET_POSITION (0x0133) [HiMem = 7]
 *    Get file pointer for random access
 *
 * Inputs:  B
 * Output:     (and on failure A)
 */
#define ZXN_DOS_GET_POSITION       0x0133, 7

/*
 * ZXN_DOS_SET_POSITION (0x0136) [HiMem = 7]
 *    Set file pointer for random access
 *
 * Inputs:  B,HL
 * Output:     (and on failure A)
 */
#define ZXN_DOS_SET_POSITION       0x0136, 7

/*
 * ZXN_DOS_GET_EOF (0x0139) [HiMem = 7]
 *    Get end of file position for random access
 *
 * Inputs:  B
 * Output:     (and on failure A)
 */
#define ZXN_DOS_GET_EOF            0x0139, 7

/*
 * ZXN_DOS_GET_1346 (0x013C) [HiMem = 7]
 *    Get memory usage in pages 1, 3, 4, 6
 *
 * Inputs:  
 * Output:  D,E,H,L
 */
#define ZXN_DOS_GET_1346           0x013C, 7

/*
 * ZXN_DOS_SET_1346 (0x013F) [HiMem = 7]
 *    Re-allocate memory usage in pages 1, 3, 4, 6
 *
 * Inputs:  D,E,H,L
 * Output:     (and on failure A)
 */
#define ZXN_DOS_SET_1346           0x013F, 7

/*
 * ZXN_DOS_FLUSH (0x0142) [HiMem = 7]
 *    Bring disk up to date
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_DOS_FLUSH              0x0142, 7

/*
 * ZXN_DOS_SET_ACCESS (0x0145) [HiMem = 7]
 *    Change open file's access mode
 *
 * Inputs:  B,C
 * Output:     (and on failure A)
 */
#define ZXN_DOS_SET_ACCESS         0x0145, 7

/*
 * ZXN_DOS_SET_ATTRIBUTES (0x0148) [HiMem = 7]
 *    Change a file's attributes
 *
 * Inputs:  D,E,HL
 * Output:     (and on failure A)
 */
#define ZXN_DOS_SET_ATTRIBUTES     0x0148, 7

/*
 * ZXN_DOS_SET_MESSAGE (0x014E) [HiMem = 7]
 *    Enable/disable error messages
 *
 * Inputs:  A,HL
 * Output:  HL,DE,A,B,C,D,E
 */
#define ZXN_DOS_SET_MESSAGE        0x014E, 7

/*
 * ZXN_IDE_VERSION (0x00A0) [HiMem = 7]
 *    Get IDEDOS version number
 *
 * Inputs:  
 * Output:  D,E
 */
#define ZXN_IDE_VERSION            0x00A0, 7

/*
 * ZXN_IDE_SWAP_OPEN (0x00D9) [HiMem = 7]
 *    Open a swap partition
 *
 * Inputs:  A,BC
 * Output:  IX   (and on failure A)
 */
#define ZXN_IDE_SWAP_OPEN          0x00D9, 7

/*
 * ZXN_IDE_SWAP_CLOSE (0x00DC) [HiMem = 7]
 *    Close a swap partition
 *
 * Inputs:  IX
 * Output:  
 */
#define ZXN_IDE_SWAP_CLOSE         0x00DC, 7

/*
 * ZXN_IDE_SWAP_OUT (0x00DF) [HiMem = 7]
 *    Write block to swap partition
 *
 * Inputs:  IX,B,HL
 * Output:  HL   (and on failure A)
 */
#define ZXN_IDE_SWAP_OUT           0x00DF, 7

/*
 * ZXN_IDE_SWAP_IN (0x00E2) [HiMem = 7]
 *    Read block from swap partition
 *
 * Inputs:  IX,B,HL
 * Output:  HL   (and on failure A)
 */
#define ZXN_IDE_SWAP_IN            0x00E2, 7

/*
 * ZXN_IDE_SWAP_EX (0x00E5) [HiMem = 7]
 *    Exchange block with swap partition
 *
 * Inputs:  IX,B,HL
 * Output:  HL   (and on failure A)
 */
#define ZXN_IDE_SWAP_EX            0x00E5, 7

/*
 * ZXN_IDE_SWAP_POS (0x00E8) [HiMem = 7]
 *    Get current block number in swap partition
 *
 * Inputs:  IX
 * Output:  BC   (and on failure A)
 */
#define ZXN_IDE_SWAP_POS           0x00E8, 7

/*
 * ZXN_IDE_SWAP_MOVE (0x00EB) [HiMem = 7]
 *    Set current block number in swap partition
 *
 * Inputs:  IX,BC
 * Output:     (and on failure A)
 */
#define ZXN_IDE_SWAP_MOVE          0x00EB, 7

/*
 * ZXN_IDE_SWAP_RESIZE (0x00EE) [HiMem = 7]
 *    Change block size of swap partition
 *
 * Inputs:  IX,A,BC
 * Output:     (and on failure A)
 */
#define ZXN_IDE_SWAP_RESIZE        0x00EE, 7

/*
 * ZXN_IDE_PARTITION_FIND (0x00B5) [HiMem = 7]
 *    Find named partition
 *
 * Inputs:  A,HL
 * Output:  BC   (and on failure A)
 */
#define ZXN_IDE_PARTITION_FIND     0x00B5, 7

/*
 * ZXN_IDE_DOS_MAP (0x00F1) [HiMem = 7]
 *    Map drive to partition
 *
 * Inputs:  A,BC,L
 * Output:     (and on failure A)
 */
#define ZXN_IDE_DOS_MAP            0x00F1, 7

/*
 * ZXN_IDE_DOS_UNMAP (0x00F4) [HiMem = 7]
 *    Unmap drive
 *
 * Inputs:  L
 * Output:     (and on failure A)
 */
#define ZXN_IDE_DOS_UNMAP          0x00F4, 7

/*
 * ZXN_IDE_DOS_MAPPING (0x00F7) [HiMem = 7]
 *    Get drive mapping
 *
 * Inputs:  L,BC
 * Output:  A,BC   (and on failure A)
 */
#define ZXN_IDE_DOS_MAPPING        0x00F7, 7

/*
 * ZXN_IDE_SNAPLOAD (0x00FD) [HiMem = 7]
 *    Load a snapshot
 *
 * Inputs:  HL
 * Output:     (and on failure A)
 */
#define ZXN_IDE_SNAPLOAD           0x00FD, 7

/*
 * ZXN_IDE_PATH (0x01b1) [HiMem = 7]
 *    Create, delete, change or get directory
 *
 * Inputs:  A,HL
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PATH               0x01b1, 7

/*
 * ZXN_IDE_CAPACITY (0x01b4) [HiMem = 7]
 *    Get card capacity
 *
 * Inputs:  C
 * Output:  DEHL   (and on failure A)
 */
#define ZXN_IDE_CAPACITY           0x01b4, 7

/*
 * ZXN_IDE_GET_LFN (0x01b7) [HiMem = 7]
 *    Get long filename
 *
 * Inputs:  HL,IX,DE,BC
 * Output:  BC,DE,HLIX   (and on failure A)
 */
#define ZXN_IDE_GET_LFN            0x01b7, 7

/*
 * ZXN_IDE_BROWSER (0x01ba) [HiMem = 7]
 *    File browser
 *
 * Inputs:  HL,DE,A
 * Output:  HL,DE   (and on failure A)
 */
#define ZXN_IDE_BROWSER            0x01ba, 7

/*
 * ZXN_IDE_MOUNT (0x01d2) [HiMem = 7]
 *    Unmount/remount SD cards
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_IDE_MOUNT              0x01d2, 7

/*
 * ZXN_IDE_STREAM_OPEN (0x0056) [HiMem = 0]
 *    Open stream to a channel
 *
 * Inputs:  A,DE,BC
 * Output:     (and on failure A)
 */
#define ZXN_IDE_STREAM_OPEN        0x0056, 0

/*
 * ZXN_IDE_STREAM_CLOSE (0x0059) [HiMem = 0]
 *    Close stream and attached channel
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_IDE_STREAM_CLOSE       0x0059, 0

/*
 * ZXN_IDE_STREAM_IN (0x005c) [HiMem = 0]
 *    Get byte from current stream
 *
 * Inputs:  
 * Output:  A
 */
#define ZXN_IDE_STREAM_IN          0x005c, 0

/*
 * ZXN_IDE_STREAM_OUT (0x005f) [HiMem = 0]
 *    Write byte to current stream
 *
 * Inputs:  C
 * Output:  A
 */
#define ZXN_IDE_STREAM_OUT         0x005f, 0

/*
 * ZXN_IDE_STREAM_PTR (0x0062) [HiMem = 0]
 *    Get or set pointer information for current stream
 *
 * Inputs:  B,DEHL
 * Output:  DEHL,B,A
 */
#define ZXN_IDE_STREAM_PTR         0x0062, 0

/*
 * ZXN_IDE_BANK (0x01bd) [HiMem = 7]
 *    Allocate or free 8K banks in ZX or DivMMC memory
 *
 * Inputs:  H,L,E
 * Output:  E   (and on failure A)
 */
#define ZXN_IDE_BANK               0x01bd, 7

/*
 * ZXN_IDE_BASIC (0x01c0) [HiMem = 0]
 *    Execute a BASIC command line
 *
 * Inputs:  HL
 * Output:  
 */
#define ZXN_IDE_BASIC              0x01c0, 0

/*
 * ZXN_IDE_WINDOW_LINEIN (0x01c3) [HiMem = 7]
 *    Input line from current window stream
 *
 * Inputs:  HL,A,E
 * Output:  E
 */
#define ZXN_IDE_WINDOW_LINEIN      0x01c3, 7

#define zxn_ide_window_linein(lowaddr, bsize, nchars)			\
    (dyncode_zx_romcall(						\
	DYNCODE_LOAD_A(bsize),						\
	DYNCODE_LOAD_E(nchars),						\
	DYNCODE_LOAD_HL(lowaddr),					\
	DYNCODE_ZXN_P3DOS_CALL(ZXN_IDE_WINDOW_LINEIN),			\
	DYNCODE_LOAD_H(0),						\
	DYNCODE_LOAD_L_E,						\
	DYNCODE_DONE							\
	))
	
	
/*
 * ZXN_IDE_WINDOW_STRING (0x01c6) [HiMem = 7]
 *    Output string to current window stream
 *
 * Inputs:  HL,E
 * Output:  
 */
#define ZXN_IDE_WINDOW_STRING      0x01c6, 7

#define zxn_ide_window_string(lowaddr, nchars)			\
    ((void) dyncode_zx_romcall(					\
	DYNCODE_LOAD_E(nchars),					\
	DYNCODE_LOAD_HL__, DYNCODE___(lowaddr),			\
	DYNCODE_ZXN_P3DOS_JUMP(ZXN_IDE_WINDOW_LINEIN)		\
	))

/*
 * ZXN_IDE_INTEGER_VAR (0x01c9) [HiMem = 7]
 *    Get or set NextBASIC integer variable
 *
 * Inputs:  B,C,L,H,DE
 * Output:  DE,H   (and on failure A)
 */
#define ZXN_IDE_INTEGER_VAR        0x01c9, 7

#define zxn_ide_integer_var(v,rw,val)				\
    ((unsigned short) dyncode_zx_romcall(			\
	DYNCODE_LOAD_B(0),					\
	DYNCODE_LOAD_C(v-'A'),					\
	DYNCODE_LOAD_DE__, DYNCODE___(val),			\
	DYNCODE_LOAD_H(rw),					\
	DYNCODE_LOAD_L(0),					\
	DYNCODE_ZXN_P3DOS_CALL_ERR(ZXN_IDE_INTEGER_VAR),	\
	DYNCODE_SWAP_DE_HL,					\
	DYNCODE_DONE						\
	))

/*
 * ZXN_IDE_RTC (0x01cc) [HiMem = 7]
 *    Query the real-time-clock module
 *
 * Inputs:  
 * Output:  BC,DE,H,L
 */
#define ZXN_IDE_RTC                0x01cc, 7

/*
 * ZXN_IDE_DRIVER (0x01cf) [HiMem = 0]
 *    Access the driver API
 *
 * Inputs:  C,B,DE
 * Output:  
 */
#define ZXN_IDE_DRIVER             0x01cf, 0

/*
 * ZXN_IDE_MODE (0x01d5) [HiMem = 7]
 *    Query NextBASIC display mode info, or change mode
 *
 * Inputs:  A,B,C
 * Output:  A,H,L,E,D,B,C,IX   (and on failure A)
 */
#define ZXN_IDE_MODE               0x01d5, 7

#define zxn_ide_mode_set(mode, submode,					\
			 OUTOPT_mode, OUTOPT_lines, OUTOPT_cols,	\
			 OUTOPT_attrs, OUTOPT_l2paper,			\
			 OUTOPT_charwidth, OUTOPT_flags)		\
    ((short) dyncode_zx_romcall(					\
	DYNCODE_LOAD_A(1),						\
	DYNCODE_LOAD_B(mode),						\
	DYNCODE_LOAD_C(submode),					\
	DYNCODE_ZXN_P3DOS_CALL_ERR(ZXN_IDE_MODE),			\
	DYNCODE_OPT_STORE_A(OUTOPT_mode)				\
	DYNCODE_OPT_STOREviaA_H(OUTOPT_lines)				\
	DYNCODE_OPT_STOREviaA_L(OUTOPT_cols)				\
	DYNCODE_OPT_STOREviaA_E(OUTOPT_attrs)				\
	DYNCODE_OPT_STOREviaA_D(OUTOPT_l2paper)				\
	DYNCODE_OPT_STOREviaA_B(OUTOPT_charwidth)			\
	DYNCODE_OPT_STOREviaA_C(OUTOPT_flags)				\
	DYNCODE_PUSH_IX,						\
	DYNCODE_POP_HL,							\
	DYNCODE_DONE							\
	))

/*
 * ZXN_IDE_TOKENISER (0x01d8) [HiMem = 7]
 *    Convert BASIC between plain text & tokenised forms
 *
 * Inputs:  B,C,HL,DE,BC
 * Output:  B,HL,BC,DE   (and on failure A)
 */
#define ZXN_IDE_TOKENISER          0x01d8, 7

#define zxn_ide_tokenizer(detok, bank, bankoffset)		\
    zxn_p3call(zxn_p3cont_generic, ZXN_IDE_TOKENISER,		\
               0, ((detok) << 8) | bank , 0, bankoffset, 0)

/*
 * ZXN_DOS_REF_XDPB (0x0151) [HiMem = 7]
 *    Point at XDPB for low level disk access
 *
 * Inputs:  A
 * Output:     (and on failure A)
 */
#define ZXN_DOS_REF_XDPB           0x0151, 7

/*
 * ZXN_DD_L_XDPB (0x0187) [HiMem = 7]
 *    Initialise an XDPB from a disk specification
 *
 * Inputs:  IX,HL
 * Output:     (and on failure A)
 */
#define ZXN_DD_L_XDPB              0x0187, 7

/*
 * ZXN_DD_L_DPB (0x018A) [HiMem = 7]
 *    Initialise a DPB from a disk specification
 *
 * Inputs:  IX,HL
 * Output:     (and on failure A)
 */
#define ZXN_DD_L_DPB               0x018A, 7

/*
 * ZXN_DOS_INITIALISE (0x0100) [HiMem = 7]
 *    Initialise +3DOS
 *
 * Inputs:  
 * Output:     (and on failure A)
 */
#define ZXN_DOS_INITIALISE         0x0100, 7

/*
 * ZXN_IDE_INTERFACE (0x00A3) [HiMem = 7]
 *    Initialise card interfaces
 *
 * Inputs:  
 * Output:  A
 */
#define ZXN_IDE_INTERFACE          0x00A3, 7

/*
 * ZXN_IDE_INIT (0x00A6) [HiMem = 7]
 *    Initialise IDEDOS
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_IDE_INIT               0x00A6, 7

/*
 * ZXN_IDE_DRIVE (0x00A9) [HiMem = 7]
 *    Get unit handle
 *
 * Inputs:  A
 * Output:  IX   (and on failure A)
 */
#define ZXN_IDE_DRIVE              0x00A9, 7

/*
 * ZXN_IDE_SECTOR_READ (0x00AC) [HiMem = 7]
 *    Low-level sector read
 *
 * Inputs:  IX,B,HL,CDE
 * Output:  HL   (and on failure A)
 */
#define ZXN_IDE_SECTOR_READ        0x00AC, 7

/*
 * ZXN_IDE_SECTOR_WRITE (0x00AF) [HiMem = 7]
 *    Low-level sector write
 *
 * Inputs:  IX,B,HL,CDE
 * Output:  HL   (and on failure A)
 */
#define ZXN_IDE_SECTOR_WRITE       0x00AF, 7

/*
 * ZXN_IDE_PARTITON_READ (0x00C4) [HiMem = 7]
 *    Read a partition entry
 *
 * Inputs:  A,BC,HL
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PARTITON_READ      0x00C4, 7

/*
 * ZXN_IDE_PARTITION_OPEN (0x00CD) [HiMem = 7]
 *    Open a partition
 *
 * Inputs:  A,BC
 * Output:  IX   (and on failure A)
 */
#define ZXN_IDE_PARTITION_OPEN     0x00CD, 7

/*
 * ZXN_IDE_PARTITION_CLOSE (0x00D0) [HiMem = 7]
 *    Close a partition
 *
 * Inputs:  IX
 * Output:  
 */
#define ZXN_IDE_PARTITION_CLOSE    0x00D0, 7

/*
 * ZXN_IDE_PARTITIONS (0x01a5) [HiMem = 7]
 *    Get number of open partitions
 *
 * Inputs:  A
 * Output:  A,HL
 */
#define ZXN_IDE_PARTITIONS         0x01a5, 7

/*
 * ZXN_DOS_OPEN_DRIVE (0x014B) [HiMem = 7]
 *    Open a drive as a single file
 *
 * Inputs:  A,B,C
 * Output:     (and on failure A)
 */
#define ZXN_DOS_OPEN_DRIVE         0x014B, 7

/*
 * ZXN_DOS_MAP_B (0x0154) [HiMem = 7]
 *    Map B: onto unit 0 or 1
 *
 * Inputs:  C,HL
 * Output:     (and on failure A,HL)
 */
#define ZXN_DOS_MAP_B              0x0154, 7

/*
 * ZXN_DD_INTERFACE (0x0157) [HiMem = 7]
 *    Is the floppy disk driver interface present?
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DD_INTERFACE           0x0157, 7

/*
 * ZXN_DD_INIT (0x015A) [HiMem = 7]
 *    Initialise disk driver
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DD_INIT                0x015A, 7

/*
 * ZXN_DD_SETUP (0x015D) [HiMem = 7]
 *    Specify drive parameters
 *
 * Inputs:  HL
 * Output:  
 */
#define ZXN_DD_SETUP               0x015D, 7

/*
 * ZXN_DD_SET_RETRY (0x0160) [HiMem = 7]
 *    Set try/retry count
 *
 * Inputs:  A
 * Output:  
 */
#define ZXN_DD_SET_RETRY           0x0160, 7

/*
 * ZXN_DD_READ_SECTOR (0x0163) [HiMem = 7]
 *    Read a sector
 *
 * Inputs:  B,C,D,E,HL,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_READ_SECTOR         0x0163, 7

/*
 * ZXN_DD_WRITE_SECTOR (0x0166) [HiMem = 7]
 *    Write a sector
 *
 * Inputs:  B,C,D,E,HL,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_WRITE_SECTOR        0x0166, 7

/*
 * ZXN_DD_CHECK_SECTOR (0x0169) [HiMem = 7]
 *    Check a sector
 *
 * Inputs:  B,C,D,E,HL,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_CHECK_SECTOR        0x0169, 7

/*
 * ZXN_DD_FORMAT (0x016C) [HiMem = 7]
 *    Format a track
 *
 * Inputs:  B,C,D,E,HL,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_FORMAT              0x016C, 7

/*
 * ZXN_DD_READ_ID (0x016F) [HiMem = 7]
 *    Read a sector identifier
 *
 * Inputs:  C,D,IX
 * Output:     (and on failure A,HL)
 */
#define ZXN_DD_READ_ID             0x016F, 7

/*
 * ZXN_DD_TEST_UNSUITABLE (0x0172) [HiMem = 7]
 *    Test media suitability
 *
 * Inputs:  C,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_TEST_UNSUITABLE     0x0172, 7

/*
 * ZXN_DD_LOGIN (0x0175) [HiMem = 7]
 *    Log in disk, initialise XDPB
 *
 * Inputs:  C,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_LOGIN               0x0175, 7

/*
 * ZXN_DD_SEL_FORMAT (0x0178) [HiMem = 7]
 *    Pre-initialise XDPB for DD FORMAT
 *
 * Inputs:  A,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_SEL_FORMAT          0x0178, 7

/*
 * ZXN_DD_ASK_1 (0x017B) [HiMem = 7]
 *    Is unit 1 (external drive) present?
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DD_ASK_1               0x017B, 7

/*
 * ZXN_DD_DRIVE_STATUS (0x017E) [HiMem = 7]
 *    Fetch drive status
 *
 * Inputs:  C
 * Output:  A
 */
#define ZXN_DD_DRIVE_STATUS        0x017E, 7

/*
 * ZXN_DD_EQUIPMENT (0x0181) [HiMem = 7]
 *    What type of drive?
 *
 * Inputs:  C,IX
 * Output:  A
 */
#define ZXN_DD_EQUIPMENT           0x0181, 7

/*
 * ZXN_DD_ENCODE (0x0184) [HiMem = 7]
 *    Set intercept routine for copy protection
 *
 * Inputs:  A,HL
 * Output:  HL,C,D,E,IX
 */
#define ZXN_DD_ENCODE              0x0184, 7

/*
 * ZXN_DD_L_SEEK (0x018D) [HiMem = 7]
 *    uPD765A seek driver
 *
 * Inputs:  C,D,IX
 * Output:     (and on failure A)
 */
#define ZXN_DD_L_SEEK              0x018D, 7

/*
 * ZXN_DD_L_READ (0x0190) [HiMem = 7]
 *    uPD765A read driver
 *
 * Inputs:  HL
 * Output:  HL
 */
#define ZXN_DD_L_READ              0x0190, 7

/*
 * ZXN_DD_L_WRITE (0x0193) [HiMem = 7]
 *    uPD765A write driver
 *
 * Inputs:  HL
 * Output:  HL
 */
#define ZXN_DD_L_WRITE             0x0193, 7

/*
 * ZXN_DD_L_ON_MOTOR (0x0196) [HiMem = 7]
 *    Motor on, wait for motor-on time
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DD_L_ON_MOTOR          0x0196, 7

/*
 * ZXN_DD_L_T_OFF_MOTOR (0x0199) [HiMem = 7]
 *    Start the motor-off ticker
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DD_L_T_OFF_MOTOR       0x0199, 7

/*
 * ZXN_DD_L_OFF_MOTOR (0x019C) [HiMem = 7]
 *    Turn the motor off
 *
 * Inputs:  
 * Output:  
 */
#define ZXN_DD_L_OFF_MOTOR         0x019C, 7

/*
 * ZXN_IDE_FORMAT (0x00B2) [HiMem = 7]
 *    Format a partition
 *
 * Inputs:  A,BC,IX,H,L
 * Output:     (and on failure A)
 */
#define ZXN_IDE_FORMAT             0x00B2, 7

/*
 * ZXN_IDE_PARTITION_NEW (0x00B8) [HiMem = 7]
 *    Create partition
 *
 * Inputs:  A,HL
 * Output:  BC   (and on failure A)
 */
#define ZXN_IDE_PARTITION_NEW      0x00B8, 7

/*
 * ZXN_IDE_PARTITION_INIT (0x00BB) [HiMem = 7]
 *    Initialise partition
 *
 * Inputs:  A,BC,L,IX
 * Output:     (and on failure A,IX)
 */
#define ZXN_IDE_PARTITION_INIT     0x00BB, 7

/*
 * ZXN_IDE_PARTITION_ERASE (0x00BE) [HiMem = 7]
 *    Delete a partition
 *
 * Inputs:  A,BC
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PARTITION_ERASE    0x00BE, 7

/*
 * ZXN_IDE_PARTITION_RENAME (0x00C1) [HiMem = 7]
 *    Rename a partition
 *
 * Inputs:  A,BC,HL
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PARTITION_RENAME   0x00C1, 7

/*
 * ZXN_IDE_PARTITION_WRITE (0x00C7) [HiMem = 7]
 *    Write a partition entry
 *
 * Inputs:  A,BC,HL
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PARTITION_WRITE    0x00C7, 7

/*
 * ZXN_IDE_PARTITION_WINFO (0x00CA) [HiMem = 7]
 *    Write type-specific partition information
 *
 * Inputs:  A,BC,HL
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PARTITION_WINFO    0x00CA, 7

/*
 * ZXN_IDE_PARTITION_GETINFO (0x00D3) [HiMem = 7]
 *    Get byte from type-specific partition information
 *
 * Inputs:  A,BC,L
 * Output:  A   (and on failure A)
 */
#define ZXN_IDE_PARTITION_GETINFO   0x00D3, 7

/*
 * ZXN_IDE_PARTITION_SETINFO (0x00D6) [HiMem = 7]
 *    Set byte in type-specific partition information
 *
 * Inputs:  A,BC,L,H
 * Output:     (and on failure A)
 */
#define ZXN_IDE_PARTITION_SETINFO   0x00D6, 7

/*
 * ZXN_IDE_DOS_UNPERMANENT (0x00FA) [HiMem = 7]
 *    Remove permanent drive mapping
 *
 * Inputs:  L
 * Output:     (and on failure A)
 */
#define ZXN_IDE_DOS_UNPERMANENT    0x00FA, 7

/*
 * ZXN_IDE_IDENTIFY (0x01a2) [HiMem = 7]
 *    Return IDE drive identity information
 *
 * Inputs:  B,C,HL
 * Output:  HL   (and on failure A)
 */
#define ZXN_IDE_IDENTIFY           0x01a2, 7

/*
 * ZXN_IDE_ACCESS_DATA (0x019f) [HiMem = 7]
 *    
 *
 * Inputs:  HL,DE,BC
 * Output:     (and on failure A)
 */
#define ZXN_IDE_ACCESS_DATA        0x019f, 7

/*
 * ZXN_IDE_FS_UNIT (0x01a8) [HiMem = 7]
 *    
 *
 * Inputs:  A,B,C
 * Output:     (and on failure A)
 */
#define ZXN_IDE_FS_UNIT            0x01a8, 7

/*
 * ZXN_IDE_FS_DRIVE (0x01ab) [HiMem = 7]
 *    
 *
 * Inputs:  A,B,C
 * Output:     (and on failure A)
 */
#define ZXN_IDE_FS_DRIVE           0x01ab, 7

/*
 * ZXN_IDE_FS_FILE (0x01ae) [HiMem = 7]
 *    
 *
 * Inputs:  A,B,C
 * Output:     (and on failure A)
 */
#define ZXN_IDE_FS_FILE            0x01ae, 7

#endif /* ZXN_P3CALL_H_INCLUDED */
