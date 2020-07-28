/*
* This driver provide an interface to read a button status (volume down button).
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>

#define VOL_DOWN_PIN	91

static int irq;

static int btn_open(struct inode *, struct file *);
static int btn_close(struct inode *, struct file *);
static ssize_t btn_read(struct file *, char __user *, size_t, loff_t *);

static struct file_operations fops = {
	.open = btn_open,
	.release = btn_close,
	.read = btn_read,
};

static struct miscdevice btn_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "vol_btn",
	.mode = 0777,
	.fops = &fops,
};

static irqreturn_t button_irq_handler(int irq, void *data)
{
//	pr_info("[test] jump to interrupt handler\n");
	return IRQ_HANDLED;
}

static int btn_open(struct inode *inodep, struct file *filep)
{
	//pr_info("[test] Call open\n");
	return 0;
}

static int btn_close(struct inode *inodep, struct file *filep)
{
	//pr_info("[test] Call close\n");
	return 0;
}

static ssize_t btn_read(struct file *filep, char __user *buf, size_t len,
			loff_t *ofset)
{
	int btnState;
	int ret;

	btnState = gpio_get_value(VOL_DOWN_PIN);
	ret = copy_to_user(buf, &btnState, sizeof(int));
	if (ret) {
		pr_err("Can not copy to user\n");
		return ret;
	}

	return sizeof(int);
}

static int __init button_init(void)
{
	int ret;

	if (gpio_is_valid(VOL_DOWN_PIN) < 0) {
		pr_err("[test] gpio %d is not valid\n", VOL_DOWN_PIN);
		return -EINVAL;
	}

	ret = gpio_request(VOL_DOWN_PIN, "vol_down_button");
	if (ret) {
		pr_err("[test] Can not request gpio %d\n", VOL_DOWN_PIN);
		goto req_gpio_fail;
	}

	gpio_direction_input(VOL_DOWN_PIN);
	gpio_set_debounce(VOL_DOWN_PIN, 50);
	irq = gpio_to_irq(VOL_DOWN_PIN);

	ret = request_irq(irq, (irq_handler_t)button_irq_handler,
							IRQF_TRIGGER_FALLING| IRQF_ONESHOT,
							"Vol_button", NULL);
	if (ret) {
		pr_err("[test] Request interrupt failed\n");
		goto req_irq_fail;
	}

	ret = misc_register(&btn_dev);
	if (ret) {
		pr_err("[test] Can not register misc device\n");
		goto misc_reg_fail;
	}
	pr_info("[test] Init successfully");
	return 0;

misc_reg_fail:
	free_irq(irq, NULL);
req_irq_fail:
	gpio_free(VOL_DOWN_PIN);
req_gpio_fail:
	return ret;

}

static void __exit button_exit(void)
{
	free_irq(irq, NULL);
	gpio_free(VOL_DOWN_PIN);
	misc_deregister(&btn_dev);
	pr_info("[test] Exit done!\n");
}

module_init(button_init);
module_exit(button_exit);

MODULE_LICENSE("GPL");
