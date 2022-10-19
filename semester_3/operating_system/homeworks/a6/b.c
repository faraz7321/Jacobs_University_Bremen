
#include <stdio.h>

extern void h();

int x = 1;
static double y = 1;
static char z = 'A';

static void g()
{
    puts("b.c: g()");
    h();
}

void f()
{
    puts("b.c: f()");
    g();
}