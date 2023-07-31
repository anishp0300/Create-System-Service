#ifndef ANDROID_SIGMASERVICE_INTERFACE_H
#define ANDROID_SIGMASERVICE_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware/hardware.h>

__BEGIN_DECLS

#define SIGMASERVICE_HARDWARE_MODULE_ID "sigmaservice"

struct sigmaservice_device_t {
    struct hw_device_t common;

    int(*retString)(char* buffer, int num);
    int(*give)(char* buffer, int num);;
};

__END_DECLS
#endif
