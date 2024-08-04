// Includes
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/proc_fs.h>
#include <linux/vmalloc.h>

// Predeclares
ssize_t kudo_read(struct file *file, char __user *user, size_t size, loff_t *off);
ssize_t kudo_write(struct file *file, const char __user *user, size_t size, loff_t *off);

// The Global Proc File Reference
static struct proc_dir_entry *kudo_proc = NULL;

// On Read
ssize_t kudo_read(struct file *file, char __user *user, size_t size, loff_t *off)
{
    return 0;
}

// On Write
ssize_t kudo_write(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    char *user_buffer;
    short use_multipage = 0;
    if (size > PAGE_SIZE) {
        use_multipage = 1;
        user_buffer = vmalloc(size);
    }else{
        user_buffer = kmalloc(size, GFP_KERNEL);
    }

    if (user_buffer == NULL){
        printk(KERN_ERR "Failed to allocate %lu bytes of memory.", size);
        return size;
    }

    memset(user_buffer, 0x0, size);
    
    copy_from_user(user_buffer, user, size);    

    printk(KERN_DEBUG "Got Input: %s", user_buffer);

    // Arguments for the user-space program
    char *argv[] = { "/bin/sh", "-c", user_buffer, (char *) NULL };
    // Environment variables
    char *envp[] = { "HOME=/", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
    int ret;

    // Execute the user-space program
    ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
    if (ret != 0) {
        printk(KERN_ERR "Error executing user-space program: %d\n", ret);
    }

    if (use_multipage == 1){
        vfree(user_buffer);
    }else{
        kfree(user_buffer);
    }
    return size;
}

static const struct proc_ops kudo_proc_fops =
{
    .proc_read = kudo_read,
    .proc_write = kudo_write,
};

// On Load
static int __init kudo_init(void)
{
    printk(KERN_INFO "Kudo Module Loaded\n");
    kudo_proc = proc_create("kudo_interface", 0600, NULL, &kudo_proc_fops);
    if (kudo_proc == NULL)
    {
        return -1;
    }
    
    return 0;
}

// On Unload
static void __exit kudo_exit(void)
{
    printk(KERN_INFO "Kudo Module Unloaded\n");
    proc_remove(kudo_proc);
}

// Metadata
module_init(kudo_init);
module_exit(kudo_exit);

MODULE_DESCRIPTION("Adds command kudo to run code in the kernel");
MODULE_AUTHOR("Jacob Freeman");
MODULE_LICENSE("GPL");
