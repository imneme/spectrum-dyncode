# ZX Sectrum Dynamic Code and ROM Calls (for z88dk)

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

To call the tape loading routine, we need to pass three parameters in
registers, as well as set or clear the carry flag.

This C code implements the call:

```c
#define zx_rom_ld_bytes(type, loadNotVerify, start, length)             \
    ((void) dyncode_zx_romcall(                                         \
        DYNCODE_LOAD_A(type),                                           \
        DYNCODE_LOAD_IX__, DYNCODE___(start),                           \
        DYNCODE_LOAD_DE__, DYNCODE___(length),                          \
        loadNotVerify ? DYNCODE_SET_C : DYNCODE_SET_Z,                  \
        DYNCODE_JUMP__, DYNCODE___(ZX_ROM_LD_BYTES)                     \
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
```

Then `dyncode_zx_romcall` sets things up and then calls this code.

Note that if we had selected verify, it would instead have generated this
code:
```
    ld a,0
    ld ix, $a000
    ld de, 1000
    cp a
    jp $0556
```
where `cp a` would have cleared the carry flag.

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

But in any case, this the _fun_ way.  There is something rather
awesome about dynamically generating Z80 code on the fly.  This is a
rather simple case, but perhaps you can come up with cleverer uses of
this approach.
