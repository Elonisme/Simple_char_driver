#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simple_char_driver"
#define BUF_LEN 1024

static char device_buffer[BUF_LEN];
static int major_number;

static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
    ssize_t bytes_read = 0;
    if (*offset >= BUF_LEN)
        return 0;

    if (*offset + length > BUF_LEN)
        length = BUF_LEN - *offset;

    if (copy_to_user(buffer, device_buffer + *offset, length) != 0)
        return -EFAULT;

    *offset += length;
    bytes_read = length;

    printk(KERN_INFO "Read %zu bytes from device\n", length);
    return bytes_read;
}

static ssize_t device_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
    ssize_t bytes_written = 0;
    if (*offset >= BUF_LEN)
        return -ENOSPC;

    if (*offset + length > BUF_LEN)
        length = BUF_LEN - *offset;

    if (copy_from_user(device_buffer + *offset, buffer, length) != 0)
        return -EFAULT;

    *offset += length;
    bytes_written = length;

    printk(KERN_INFO "Wrote %zu bytes to device\n", length);
    return bytes_written;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int __init simple_char_driver_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }

    printk(KERN_INFO "Registered correctly with major number %d\n", major_number);
    return 0;
}

static void __exit simple_char_driver_exit(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Unregistered the device\n");
}

module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
