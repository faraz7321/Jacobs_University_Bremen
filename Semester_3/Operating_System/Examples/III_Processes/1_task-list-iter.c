/*
 * This is a simple tasks list iteration demo.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Juergen Schoenwaelder");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple task list iteration kernel module.");

static const char *modname = __this_module.name;

static void print_tasks(void)
{
    struct task_struct *task;

    rcu_read_lock();
    for_each_process(task)
    {
        printk(KERN_INFO "%s: %8d %s\n", modname, task->pid, task->comm);
    }
    rcu_read_unlock();
}
static int __init tasks_init(void)
{
    printk(KERN_DEBUG "%s: initializing...\n", modname);
    print_tasks();
    return 0;
}
static void __exit tasks_exit(void)
{
    printk(KERN_DEBUG "%s: exiting...\n", modname);
}
module_init(tasks_init);
module_exit(tasks_exit);