/*
 * Writes "Hello World" to the console using a C library. Runs on Linux
 * rv64 Linux any other rv64 system that does not use underscores for
 * symbols in its C library. To assemble and run:
 *
 * gcc -static hello-rv64-libc.s && ./a.out
 */

        .global main
        .text
main:                                   # called by C library's startup code
        addi    sp, sp, -16             # allocate stack frame
        sd      ra, 8(sp)               # save return address
        sd      s0, 0(sp)               # save frame pointer
        addi    s0, sp, 16              # establish new frame point
        la      a0, message             # first parameter passed in a0
        jal     puts                    # call puts(message)
        addi    a0, zero, 0             # we want return code 0
        ld      ra, 8(sp)               # restore return address
        ld      s0, 0(sp)               # restore frame pointer
        addi    sp, sp, 16              # deallocate stack frame
        ret                             # return to C library code
message:
        .asciz "Hello World"            # asciz puts a 0 byte at the end
