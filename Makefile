CC = zcc +zx -SO3 -clib=sdcc_iy
# CC = zcc +zx -O3 -clib=new

DYNCODE_OBJS = dyncode_zx_romcall_stdstack.o dyncode_zx_romcall.o	\
		dyncode_preserve_ix.o dyncode_quick.o \
		dyncode_zx_romcall_stdstack_err.o \
		jump_hl.o zx_exit_msg.o \
		p3call_private.o

TARGETS = dyncode.lib example.tap p3call_example.tap

%.o: %.asm
	z80asm $<

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(DYNCODE_OBJS)

example.tap: example.c zx_romcall.h dyncode.h
	$(CC) $< -o example -I. -ldyncode -startup=30 -create-app

p3call_example.tap: p3call_example.c zxn_p3call.h dyncode.h
	$(CC) $< -o p3call_example -I. -ldyncode -startup=30 -create-app

dyncode.lib: $(DYNCODE_OBJS)
	z80asm --make-lib=$@ $^

dyncode_zx_romcall_stdstack_err.o: dyncode_zx_romcall_stdstack_err.asm
dyncode_zx_romcall_stdstack.o: dyncode_zx_romcall_stdstack.asm
dyncode_zx_romcall.o: dyncode_zx_romcall.asm
dyncode_preserve_ix.o: dyncode_preserve_ix.asm
dyncode_quick.o: dyncode_quick.asm
jump_hl.o: jump_hl.asm
zx_exit_msg.o: zx_exit_msg.asm
p3call_private.o: p3call_private.asm
