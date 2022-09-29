/*
 * hello-dll.c --
 *
 *      This program uses the dynamic linking API to locate the puts()
 *      function in the C library and then uses it to print a message.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#if defined(__linux__)
#define LIBC "/lib/x86_64-linux-gnu/libc.so.6"
#elif defined(__APPLE__)
#define LIBC "/usr/lib/libc.dylib"
#else
#define LIBC "libc.so"
#endif

int main()
{
    void *handle;
    void (*println) (char *);
    char *error;

    handle = dlopen(LIBC, RTLD_LAZY);
    if (! handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    println = dlsym(handle, "puts");
#pragma GCC diagnostic pop
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    
    println("hello world");
    (void) dlclose(handle);
    
    return EXIT_SUCCESS;
}
