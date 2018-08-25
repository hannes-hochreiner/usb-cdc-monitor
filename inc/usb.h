#ifndef __USB_H__
#define __USB_H__

#include <stdlib.h>
#include <stdio.h>
#include <libusb-1.0/libusb.h>

int reportUsbError(int res);
void cleanupAndExit(struct libusb_config_descriptor* conf, libusb_device_handle* devHndl);
int initUsb();

#endif
