#include <stdio.h>
#include <stdlib.h>
#include <zx_romcall.h>

void chan_open(char chan) __z88dk_fastcall
{
    zx_rom_chan_open(chan);
}

short editor_error()
{
    chan_open(2);
    printf("Oh yeah? (ERR_NR=%d)\n", *((char*)0x5C3A));
    *((char*)0x5C3A) = 0xff;
    chan_open(1);
    return 1;
}

int main()
{
    int i;
    short free_mem;
    char key;
    char *cursor_pos;
    char *cp;
    zx_rom_cls();
    chan_open(2);
    printf("Hello World\n");
    chan_open(1);
    zx_rom_pr_string("Press a key: ",13);
    chan_open(2);
    for (i = 0; i < 256; ++i)
	zx_rom_plot_sub(i,i/2);
    zx_rom_beeper(0x0040, 0x066a);

    chan_open(1);
    zx_rom_set_min();
    cursor_pos = (char*) zx_rom_bc_spaces(1, SKIP);
    *cursor_pos = '\r';
    *((char*) 0x5C71) |= 0xa0;        // Set bits 7 and 5 of FLAGX
//  None of these lines are needed/helpful.
//  *((char*) 0x5c3c) |= 8;           // Set bit 3 of TV_FLAG
//  *((char*) 0x5C71) &= 0xbf;        // Clear bit 6 of FLAGX (not needed here)
//  *((char*) 0x5c3b) |= 0x0c;        // Set bits 2 and 3 of FLAGS (N/A)
    *((char**) 0x5C5B) = cursor_pos;  // Set K_CUR to cursor position.
    key = zx_rom_wait_key();
    putchar(' ');
    putchar(0x08);
    chan_open(2);
    printf("You pressed '%c'\n", key);
    printf("Pausing...\n");
    zx_rom_pause_1(100);
    zx_rom_cls_lower();
    chan_open(1);
    zx_rom_pr_string("Prompt> ",8);
    while (zx_rom_editor(editor_error))
	;
    chan_open(2);
    cp = cursor_pos;
    while (*cp != '\r')
	++cp;
    *cp = '\0';
    printf("You entered: '%s'\n", cursor_pos);

    // This value is naccurate because the stack is moved above RAMTOP
    free_mem = 65535 - (unsigned short)zx_rom_test_room(0);
    // IF we didn't move the stack during the rom call, to where BASIC
    // expects it, we'd need to correct it (assuming org 32768).
    // free_mem -= ((unsigned short)get_sp(0)) - 32768;
    printf("%u bytes free for BASIC.\n", free_mem);

    zx_exit_msg("0 See you NEXT time", 0xff);

    return 0;
}
