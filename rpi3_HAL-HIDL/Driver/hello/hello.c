#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/uaccess.h>   
#include <linux/slab.h>
#include <linux/string.h>

MODULE_AUTHOR("PHONGLT9");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");


/*define GPIO reg*/
#define GPIO_BASE      0x3F200000
#define GPFSEL2             0x08
#define GPSET0              0x1C
#define GPCLR0              0x28                         
#define GPLEV0              0x34

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

// #define MAGIC_NO    100
// #define ON  _IOW(MAGIC_NO, 0, char*)
// #define OFF _IOW(MAGIC_NO, 1, char*)

static void __iomem *io;
static char * ker_buff;
static unsigned long temp;

struct _vchar_drv {
    dev_t dev_numb;
    struct class *dev_class;
    struct device *dev;
    struct cdev *my_cdev;
}vchar_drv;

static int dev_open(struct inode *, struct file *);
static int dev_close(struct inode *, struct file *);
static ssize_t dev_read(struct file *fp, char __user *buf, size_t len, loff_t *off);
static ssize_t dev_write(struct file *fp, const char __user *buf, size_t len, loff_t *off);

static void setup_led(void);
static void led_on(void);
static void led_off(void);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_close,
    .write = dev_write,
    .read  = dev_read,
    // .unlocked_ioctl = dev_ioctl,
};

void led_off()
{
    /*turn off led*/
	temp = ioread32(io + GPCLR0);
	temp = temp&(1 << 21);
	iowrite32(temp , (io +GPCLR0));

    temp = ioread32(io + GPSET0);
	temp = temp&(0 << 21);
	iowrite32(temp , (io +GPSET0));
}

void led_on()
{
    /*turn on led*/
	temp = ioread32(io + GPSET0);
	temp = temp&(1 << 21);
	iowrite32(temp , (io +GPSET0));

    temp = ioread32(io + GPCLR0);
	temp = temp&(0 << 21);
	iowrite32(temp , (io +GPCLR0));
    printk(" AAAAA : %ld", (temp >> 21) & 1);
}

void setup_led()
{
    /*setup blink led */
    io = ioremap(GPIO_BASE, 0x100);
    if(io == NULL)
        pr_alert("fail map base address\n");

    temp = ioread32(io + GPFSEL2);
    temp = temp | (GPIO_OUTPUT << 3);
    iowrite32(temp, io + GPFSEL2);
}

static ssize_t dev_read(struct file *fp, char __user *user_buf, size_t len, loff_t *off)
{
    int size;

    temp = ioread32(io + GPLEV0);
    if(((temp >> 21) & 1) == 1) {
        size = copy_to_user(user_buf, "led_on", sizeof("led_on"));
        return sizeof("led_on");
    }
    else if(((temp >> 21) & 1) == 0) {
        size = copy_to_user(user_buf, "led_off", sizeof("led_off"));
        return sizeof("led_off");
    }

	return 0;
}
static ssize_t dev_write(struct file *fp, const char __user *user_buf, size_t len, loff_t *off)
{
    int size;

	memset(ker_buff, 0, strlen(ker_buff));
	size = copy_from_user(ker_buff, user_buf, len);

	if (ker_buff[0] == '1')
		led_on();
	else if (ker_buff[0] == '0')
        led_off();
	else
		printk(KERN_INFO "Unknown command, 1 or 0\n");
	
    printk("Handle write\n");

    return len;
}

static int dev_open(struct inode *i_node, struct file *file_p)
{
    printk("Handle open\n");
    return 0;
}

static int dev_close(struct inode *i_node, struct file *file_p)
{
    printk("Handle close\n");
    return 0;
}

// static long dev_ioctl(struct file * filep, unsigned int cmd, unsigned long arg)
// {
//     switch(cmd) {
//         case ON:
//             printk("LED ON\n");
//             setup_led();
//             led_on();
//             break;
//         case OFF:
//             printk("LED OFF\n");
//             setup_led();
//             led_off();
//             break;
//         default :
//             printk("Invalid cmd\n");
//     }
//     return 0;
// }

static int __init vchar_drv_init(void)
{
    int ret = 0, i = 0;
    /* Init device number */
    vchar_drv.dev_numb = 0;
    ret = alloc_chrdev_region(&vchar_drv.dev_numb, 0, 1, "vchar_device");
    if(ret < 0) {
        printk("Failed to register device number\n");
        goto failed_register_dev_numb;
    }
    printk("MAJOR : %d, MINOR : %d", MAJOR(vchar_drv.dev_numb), MINOR(vchar_drv.dev_numb));

    /* Create device file */
    vchar_drv.dev_class = class_create(THIS_MODULE, "class_vchar_dev_led");
    if(vchar_drv.dev_class == NULL) {
        printk("Failed to create a device class\n");
        goto failed_create_dev_class;
    }

    vchar_drv.dev = device_create(vchar_drv.dev_class, NULL, vchar_drv.dev_numb, NULL, "hello_hal");
    if(IS_ERR(vchar_drv.dev)) {
        printk("Failed to create a device\n");
        goto failed_create_dev;
    }

    /* Register entry point*/
    vchar_drv.my_cdev = cdev_alloc();
    cdev_init(vchar_drv.my_cdev, &fops);
    ret = cdev_add(vchar_drv.my_cdev, vchar_drv.dev_numb, 1);
    if(ret < 0){
        printk("failed add charater device to the system\n");
        goto failed_allocate_cdev;
    }
    
    /* kmalloc ker_buff */
    ker_buff = (char *)kmalloc(20, GFP_KERNEL);
	if (ker_buff != NULL)
		printk(KERN_INFO "address alocate : 0x%p\n", ker_buff);

    setup_led();
    led_on();
    
    printk("Initialize vchar driver successfully\n");

    for(i = 0 ; i < 5; i++)
    	printk("PHONGLT9 %s %d \n",__func__, __LINE__);
    failed_register_dev_numb : 
        return ret;
    failed_create_dev_class :
        unregister_chrdev_region(vchar_drv.dev_numb, 1);
    failed_create_dev :
        class_destroy(vchar_drv.dev_class);
    failed_allocate_cdev :
        printk("do something\n");
    return 0;
}

static void __exit vchar_drv_exit(void)
{
    device_destroy(vchar_drv.dev_class, vchar_drv.dev_numb);
    class_destroy(vchar_drv.dev_class);
    unregister_chrdev_region(vchar_drv.dev_numb, 1);
    cdev_del(vchar_drv.my_cdev);

    printk("Exit vchar driver\n");
}

module_init(vchar_drv_init);
module_exit(vchar_drv_exit);
