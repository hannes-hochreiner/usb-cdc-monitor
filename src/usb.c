#include "../inc/usb.h"

int initUsb() {
  int res = libusb_init(NULL);

  if (res != 0) {
    return res;
  }
  
  libusb_set_debug(NULL, 2);

  // Raspbian is still on version 1.0.21 where the libusb_set_option call is not implemented.
  // For the time being, we'll have to live with the deprecation warning.
  // res = libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);

  return 0;
}

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
      libusb_attach_kernel_driver(devHndl, if_num);
    }

    libusb_free_config_descriptor(conf);
  }

  if (devHndl) {
    libusb_close(devHndl);
  }
  
  libusb_exit(NULL);
  exit(0);
}