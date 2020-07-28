#define LOG_TAG		"testvol"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/testvol.h>

#define FILE_NAME		"/dev/vol_btn"

static struct hw_module_methods_t vol_module_methods = {
	.open = NULL,
};

static int readstatus(volume_module_t *module)
{
	int fd;
	int status;

	fd = open(FILE_NAME, O_RDONLY);
	if (fd < 0) {
		ALOGE("Can not open file %s\n", FILE_NAME);
		return fd;
	}
	read(fd, &status, sizeof(status));
	close(fd);

	return status;
}

volume_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag		= HARDWARE_MODULE_TAG,
		.version_major 	= 1,
		.version_minor 	= 0,
		.id		= VOL_HARDWARE_ID,
		.name		= "testvol",
		.author		= "tungnt",
		.methods	= &vol_module_methods,
	},

	.read_status = readstatus,
};

