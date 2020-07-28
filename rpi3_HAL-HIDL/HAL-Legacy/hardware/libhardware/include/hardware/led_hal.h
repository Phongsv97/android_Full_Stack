/*
*	Author: PHONGLT
*	Version: 1.0
*/

#ifndef LED_HAL_H
#define LED_HAL_H

#include <stdio.h>
#include <stdint.h>
#include <hardware/hardware.h>

/* Dùng cho các tệp .h tương thích với trình biên dịch C++ */

__BEGIN_DECLS

#define LED_HARDWARE_MODULE_ID	"led_hal"

struct led_module_t {
	struct hw_module_t common;
};

struct led_device_t {
	struct hw_device_t common;
	int (*config_led)(const char *);
	int (*get_status)(const char *);
};

__END_DECLS

#endif