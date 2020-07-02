# ZX Spectrum Dynamic Code and ROM Calls (for z88dk)

There are many useful utilities in the Spectrum ROM.  However, by
default z88dk sets things up to make calling into the ROM challenging:

* The most widely used library, `sdcc_iy`, sets `IY` to an incompatible value
* The stack is placed above RAMTOP, confusing any routine that uses the stack 
  pointer in calculating free space, or errors out to BASIC via RST 8.
* Some Spectrum routines expect HL' to be the “program counter” for the ROM 
  calculator.

In addition, some rom routines may wish to crash out with an error.  Either
you want that to happen, or you want to catch the error.

The housekeeping is the about the same in all cases, but wrapping it around
the code implementing every call would be annoying.

Thus, this code allows the equivalent of anonymous functions (closures)
specify what we want done and are passed to a routine that does the
necessary setup and teardown, stack switching, etc.

For a user's perspective, see `example.c`.

## How it Works — Internals

Let's consider calling the low-level ROM routine `SV_BYTES, which is a
tape saving routine.  To call this ROM routine, we need to pass three
parameters in registers.

Because a C stub has already been `#define`d, as a user we can just call
`zx_rom_sv_bytes` and pass in the three parameters, but let's look at how
this macro is defined:

```c
#define zx_rom_sv_bytes(type, start, length)                            \
    ((void) dyncode_zx_romcall(                                         \
        DYNCODE_LOAD_A(type),                                           \
        DYNCODE_LOAD_IX__, DYNCODE___(start),                           \
        DYNCODE_LOAD_DE__, DYNCODE___(length),                          \
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_SV_BYTES)                     \
        ))
```

When called as `zx_rom_sv_bytes(0, 0xa000, 1000)`, this code will push
the following dynamic code onto the stack:

```
    ld a,0
    ld ix, $a000
    ld de, 1000
    nop
    jp $0556
```

(The `nop` is present because `DYNCODE_JUMP__` is nop-prefixed to make
it fit in 16 bits.)

Then `dyncode_zx_romcall` sets things up and then calls this code.

Now let's consider calling the ROM routine `LD_BYTES`, which is the
tape loading/verifying routine.  To call this ROM routine, we need to
pass three parameters in registers, as well as set or clear the carry
flag.  It returns its result (whether or not there was an error) in the
carry flag, which is often convenient for assembly language programmers
but not so much for C.

This C code implements the call:

```c
#define zx_rom_ld_bytes(type, loadNotVerify, start, length)             \
    ((void) dyncode_zx_romcall(                                         \
        DYNCODE_LOAD_A(type),                                           \
        DYNCODE_LOAD_IX__, DYNCODE___(start),                           \
        DYNCODE_LOAD_DE__, DYNCODE___(length),                          \
        (loadNotVerify ? DYNCODE_SET_C : DYNCODE_SET_Z) |               \
	DYNCODE_CALL__, DYNCODE___(ZX_ROM_LD_BYTES)			\
	DYNCODE_LOAD_HL__, DYNCODE___(0),				\
	DYNCODE_RET_NC |   						\
	DYNCODE_DEC_HL,							\
	DYNCODE_DONE							\
        ))
```

When called as `zx_rom_ld_bytes(0, 1, 0xa000, 1000)`, this code will push
the following dynamic code onto the stack:

```
    ld a,0
    ld ix, $a000
    ld de, 1000
    scf
    jp $0556
    ld hl,0
    ret nc
    dec hl
    ret
    nop
```

Note that if we had selected verify, it would instead have generate
`cp a` rather than `scf`.

See the code in `zx_romcall.h` for `zx_rom_bc_spaces` for code that
returns either one value (as the return value) or two (writing to a C
variable).  Note that if you don't want to write to the variable, no
code is generated to do so.

## Is this the best way?

Seasoned assembly programmers may wonder why not write a shim for the
call directly.  And that might be more efficient if carefully written,
but the nice thing about this approach is that we can write the code
to call any ROM routine without thinking too much and just coding in
C.  The stylized C code for loading registers for the call and saving
them out afterwards is always the same.

In our examples above, the code for `LD_BYTES` is short and the
overheads of generating it are low.  Whereas for `SV_BYTES`, it might
be more to instead write a hand-written stub and call that.  If you
want to go that route, the `zx_romcall` routine may help.

But in any case, this the _fun_ way.  There is something rather
awesome about dynamically generating Z80 code on the fly.  This is a
rather simple case, but perhaps you can come up with cleverer uses of
this approach.
