/*
 * This module implements a simple character device as a kernel module.
 *
 * See also http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/ctype.h>
#include <linux/mutex.h>

MODULE_AUTHOR("Juergen Schoenwaelder");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple character device kernel module.");

#define kalert(FMT, ...) \
        printk(KERN_ALERT "[%s] "FMT"\n", __this_module.name, ##__VA_ARGS__)
#define kwarn(FMT, ...) \
        printk(KERN_WARNING "[%s] "FMT"\n", __this_module.name, ##__VA_ARGS__)
#define kinfo(FMT, ...) \
        printk(KERN_INFO "[%s] "FMT"\n", __this_module.name, ##__VA_ARGS__)

static int device_major;
static const char *device_name = "echo0";
static const char *class_name = "echo";
static struct class*  echo_class  = NULL;
static struct device* echo_device = NULL;

static char buffer[128];

static char *data = NULL;
static size_t size = 0;
static size_t used = 0;
    

static DEFINE_MUTEX(echo_mutex);

static ssize_t
echo_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    if (*f_pos >= used) {
        return 0;
    }

    /* limit count to the amount of data left (if necessary) */

    if (used - *f_pos < count) {
        count = used - *f_pos;
    }

    /* copy count characters starting at f_pos to user space */
    
    if (copy_to_user(buf, data + *f_pos, count) > 0) {
        return -EFAULT;
    }

    /* update file offset and return that we copied count characters */
    
    *f_pos += count;
    return count;
}

static ssize_t
echo_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos)
{
    /* copy count characters from user space */
    
    if (copy_from_user(buffer, buf, count)) {
        return -EFAULT;
    }

    strncpy(data, buffer, size);
    used = strlen(data);

    /* update file offset and return that we copied count characters */
    
    *f_pos += count;
    return count;
}

static int
echo_open(struct inode *inode, struct file *file)
{
    if (!mutex_trylock(&echo_mutex)) {
        return -EBUSY;
    }
    return 0;
}

static int
echo_release(struct inode *inode, struct file *file)
{
    mutex_unlock(&echo_mutex);
    return 0;
}

static struct file_operations echo_fops = {
    .owner = THIS_MODULE,
    .read = echo_read,
    .write = echo_write,
    .open = echo_open,
    .release = echo_release,
};

static int
echo_cdev_create(void)
{
    /* alloate a major device number */

    device_major = register_chrdev(0, device_name, &echo_fops);
    if (device_major < 0) {
        kwarn("failed to register a major number");
        return device_major;
    }
    kinfo("device '%s', major %d, minor 0", device_name, device_major);
    
    /* register the device class */
    
    echo_class = class_create(THIS_MODULE, class_name);
    if (IS_ERR(echo_class)) {
        unregister_chrdev(device_major, class_name);
        kalert("failed to register device class '%s'", class_name);
        return PTR_ERR(echo_class);
    }
    kinfo("device class '%s' registered", class_name);

    /* register the device instance */
    
    echo_device = device_create(echo_class, NULL, MKDEV(device_major, 0),
                                NULL, device_name);
    if (IS_ERR(echo_device)) {
        class_destroy(echo_class);
        unregister_chrdev(device_major, device_name);
        kalert("failed to register the device '%s'", device_name);
        return PTR_ERR(echo_device);
    }
    kinfo("device '%s' registered", device_name);

    return 0;
}

static void
echo_cdev_cleanup(void)
{
    device_destroy(echo_class, MKDEV(device_major, 0));
    class_unregister(echo_class);
    class_destroy(echo_class);
    unregister_chrdev(device_major, device_name);
}

static int __init
echo_cdev_init(void)
{
    int rc;

    rc = echo_cdev_create();
    if (rc) {
        return rc;
    }

    /* allocate memory to hold data */

    if (! data) {
        size = sizeof(buffer) * 2;
        data = kmalloc(size, GFP_KERNEL);
        if (! data) {
            kalert("failed to allocate memory");
            echo_cdev_cleanup();
            return -ENOMEM;
        }
    }

    mutex_init(&echo_mutex);
    kinfo("module loaded");
    return 0;
}

static void __exit
echo_cdev_exit(void)
{
    if (data) {
        kfree(data);
    }
    
    mutex_destroy(&echo_mutex);
    echo_cdev_cleanup();
    kinfo("module unloaded");
}

module_init(echo_cdev_init);
module_exit(echo_cdev_exit);

