/*
 * This is a sample hello world Linux kernel module. To compile it on
 * Debian or Ubuntu, you need to install the Linux kernel headers:
 * 
 *   sudo apt-get install linux-headers-$(uname -r)
 *
 * Then type make and you are ready to install the kernel module:
 *
 *   sudo insmod ./hello.ko
 *   sudo lsmod
 *   sudo rmmod hello
 *
 * To inspect the module try this:
 *
 *   sudo modinfo ./hello.ko
 */

#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Juergen Schoenwaelder");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple hello world kernel module.");

static char *msg = "hello world";
module_param(msg, charp, 0000);
MODULE_PARM_DESC(msg, "A message to emit upon module initialization");

static const char* modname = __this_module.name;

static int __init hello_init(void)
{
    printk(KERN_DEBUG "%s: initializing...\n", modname);
    printk(KERN_INFO "%s: %s\n", modname, msg);
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_DEBUG "%s: exiting...\n", modname);
}

module_init(hello_init);
module_exit(hello_exit);
