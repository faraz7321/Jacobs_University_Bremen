/*
 * Writes "Hello World" to the console using only system calls. Runs on
 * rv64 Linux only. To assemble and run:
 *
 * gcc -c hello-rv64-syscall.s && ld -static hello-rv64-syscall.o && ./a.out
 */

        .global _start
        .text
_start:
        # write(1, message, 12)
        addi    a0, zero, 1             # file handle 1 is stdout
        la      a1, message             # address of string to write
        addi    a2, zero, 12            # number of bytes to write
        addi    a7, zero, 64            # system call 64 is write
        ecall                           # invoke write system call
        # exit(0)
        addi    a0, zero, 0             # we want return code 0
        addi    a7, zero, 93            # system call 93 is exit
        ecall                           # invoke exit system call
message:
        .ascii  "Hello World\n"
