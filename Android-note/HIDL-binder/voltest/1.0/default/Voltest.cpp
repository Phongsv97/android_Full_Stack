#include "Voltest.h"
#include <log/log.h>

namespace vendor {
namespace hardware {
namespace voltest {
namespace V1_0 {
namespace implementation {

Return<int32_t> Voltest::readstatus() {
        int32_t status;
        int fd;

        fd = open("/dev/vol_btn", O_RDONLY);
        if (fd < 0) {
                ALOGE("Can not open file\n");
                return fd;
        }

        if (read(fd, &status, sizeof(status)) < 0) {
                ALOGE("Can not read file\n");
        }
        close(fd);
    // TODO implement
        return status;
}

}
}
}
}
}
