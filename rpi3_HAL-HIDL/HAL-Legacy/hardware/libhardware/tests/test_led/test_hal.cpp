/*
*
*/

#define LOG_TAG	"test_hal"

#include <utils/misc.h>
#include <utils/Log.h>
#include <map>
#include <stdio.h>
#include <hardware/led_hal.h>


int main()
{
	int err;
	char *buff = (char *)calloc(7, sizeof(char));
	struct led_module_t *module;
	struct led_device_t *device = NULL;

	err =  hw_get_module(LED_HARDWARE_MODULE_ID, (struct hw_module_t const**)&module);
	if (err != 0) 
		printf("hw_get_module() failed (%s)\n", strerror(-err));
	else {
		if (module->common.methods->open((struct hw_module_t *)module, "", ((hw_device_t **)&device)) != 0) {
			printf("Failed : HAL open (%s)\n",strerror(-err));
			return 0;
		}
	}

	err = device->get_status(buff);
	if (err != 0) {
		printf("Faild : HAL get_status (%s)\n", strerror(-err));
		return -1;
	}

	printf("PHONGLT status: %s\n", buff);

	return 0;	
}