#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef void (*interrupt_handler)(void);

void handler_a(void)
{
    save_cpu_registers();
    save_stack_frame();
    interrupt_a_handling_logic();
    restore_stack_frame();
    restore_cpu_registers();
}
void handler_b(void)
{
    save_cpu_registers();
    save_stack_frame();
    interrupt_b_handling_logic();
    restore_stack_frame();
    restore_cpu_registers();
}

/*
 * The interrupt vector is indexed by the interrupt number. Every element
 * contains a pointer to a function handling this specific interrupt.
 */

interrupt_handler interrupt_vector[] =
    {
        handler_a,
        handler_b,
        // ...
};

#ifdef HARDWARE
/*
 * The following logic executed by the hardware when an interrupt has
 * arrived and the execution of an instruction is complete:
 */

void
interrupt(int x)
{
    handler = NULL;
    save_essential_registers(); // includes instruction pointer
    if (valid(x))
    {
        handler = interrupt_vector[x];
    }
    if (handler)
        handler();
    restore_essential_registers(); // includes instruction pointer
}
#endif
