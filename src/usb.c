#include "../inc/usb.h"

int reportUsbError(int res) {
  if (res < 0) {
    fprintf(stderr, "libusb error: %s\n", libusb_error_name(res));

    return 1;
  }

  return 0;
}

void cleanupAndExit(struct libusb_config_descriptor* conf, libusb_device_handle* devHndl) {
  if (conf) {
    for (int if_num = 0; if_num < conf->bNumInterfaces; if_num++) {
      libusb_release_interface(devHndl, if_num);
    }

    libusb_free_config_descriptor(conf);
  }

  if (devHndl) {
    libusb_close(devHndl);
  }
  
  libusb_exit(NULL);
  exit(0);
}