#ifndef ANDROID_INCLUDE_HARDWARE_VOLDOWN_H
#define ANDROID_INCLUDE_HARDWARE_VOLDOWN_H

#include <stdint.h>
#include <stdio.h>
#include <hardware/hardware.h>

__BEGIN_DECLS

#define VOL_HARDWARE_ID		"testvol"

typedef struct volume_module {
	struct hw_module_t common;
	int (*read_status)(struct volume_module *module);
} volume_module_t;

__END_DECLS

#endif
