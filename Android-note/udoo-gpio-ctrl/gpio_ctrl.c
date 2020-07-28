#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

#define DEV_NAME		"gpio_udoo"
#define GPIO_NO			102

static struct kobject *udoo_kobj;

static ssize_t gpio_val_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count)
{
	int val, ret;

	ret = kstrtoint(buf, 10, &val);
	if (ret) {
		pr_err("can not convert string\n");
		return ret;
	}
	pr_info("value is %d\n", val);
	gpio_set_value(GPIO_NO, val);

	return count;
}

static ssize_t gpio_dir_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count)
{
	int val, ret;

	ret = kstrtoint(buf, 10, &val);
	if (ret) {
		pr_err("can not convert string\n");
		return ret;
	}
	gpio_direction_output(GPIO_NO, val);

	return count;
}

static struct kobj_attribute val_attr = __ATTR(value, 0644, NULL,
						gpio_val_store);
static struct kobj_attribute dir_attr = __ATTR(direction, 0644, NULL,
							gpio_dir_store);

static struct attribute *gpio_attr[] = {
	&val_attr.attr,
	&dir_attr.attr,
	NULL,
};

static struct attribute_group gpio_attr_grp = {
	.attrs = gpio_attr,
};

static int __init gpio_ctrl_init(void)
{
	int ret;

	udoo_kobj = kobject_create_and_add(DEV_NAME, kernel_kobj->parent);
	if (!udoo_kobj) {
		pr_err("can not create kobject\n");
		return -1;
	}
	pr_info("create successfully kobject\n");

	ret = sysfs_create_group(udoo_kobj, &gpio_attr_grp);
	if (ret) {
		pr_err("can not create sysfs\n");
		return ret;
	}

	if (!gpio_is_valid(GPIO_NO)) {
		pr_err("gpio pin is not available\n");
		return -ENODEV;
	}

	ret = gpio_request(GPIO_NO, "gpio controller");
	if (ret) {
		pr_err("can not request gpio\n");
		return ret;
	}

	return ret;
}

static void __exit gpio_ctrl_exit(void)
{
	sysfs_remove_group(udoo_kobj, &gpio_attr_grp);
	kobject_put(udoo_kobj);
	gpio_free(GPIO_NO);

	pr_info("goodbye\n");
}

module_init(gpio_ctrl_init);
module_exit(gpio_ctrl_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MODULE TO CONTROL LED");
MODULE_AUTHOR("TUNG");

//Add by nguyen Thanh Tung
