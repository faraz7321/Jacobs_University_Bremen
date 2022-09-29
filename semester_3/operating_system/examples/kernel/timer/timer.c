/*
 * This is a simple timer demo.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

MODULE_AUTHOR("Juergen Schoenwaelder");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple timer kernel module.");

static int delay = 1;
module_param(delay, int, 0000);
MODULE_PARM_DESC(delay, "The timer delay in seconds");

static int count = 8;
module_param(count, int, 0000);
MODULE_PARM_DESC(count, "The number of iterations");

static const char* modname = __this_module.name;
static struct timer_list my_timer;

static void timer_callback(struct timer_list *timer)
{
    static int cnt = 0;

    printk(KERN_INFO "%s: callback #%d\n", modname, cnt);
    if (++cnt < count) {
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(delay * 1000));
    }
}

static int __init timer_init(void)
{
    printk(KERN_DEBUG "%s: initializing...\n", modname);
    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(delay * 1000));
    return 0;
}

static void __exit timer_exit(void)
{
    printk(KERN_DEBUG "%s: exiting...\n", modname);
    del_timer(&my_timer);
}

module_init(timer_init);
module_exit(timer_exit);
