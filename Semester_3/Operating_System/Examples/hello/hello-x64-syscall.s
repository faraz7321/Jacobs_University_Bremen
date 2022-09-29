/*
 * Writes "Hello World" to the console using only system calls. Runs on
 * x64 (amd64, x86_64) Linux only. To assemble and run:
 *
 * gcc -c hello-x64-syscall.s && ld -static hello-x64-syscall.o && ./a.out
 */

        .global _start
        .text
_start:
        # write(1, message, 12)
        mov     $1, %rax                # system call 1 is write
        mov     $1, %rdi                # file handle 1 is stdout
        mov     $message, %rsi          # address of string to write
        mov     $12, %rdx               # number of bytes to write
        syscall                         # invoke write system call
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke exit system call
message:
        .ascii  "Hello World\n"
