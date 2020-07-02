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
