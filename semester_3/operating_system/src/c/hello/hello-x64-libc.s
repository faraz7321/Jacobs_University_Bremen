/*
 * Writes "Hello World" to the console using a C library. Runs on
 * x64 (amd64, x86_64) Linux or any other x64 system that does not use
 * underscores for symbols in its C library. To assemble and run:
 *
 * gcc -static hello-x64-libc.s && ./a.out
 */

        .global main
        .text
main:                                   # called by C library's startup code
        mov     $message, %rdi          # first parameter passed in %rdi
        call    puts                    # call puts(message)
        ret                             # return to C library code
message:
        .asciz "Hello World"            # asciz puts a 0 byte at the end
