#include <stdio.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>
#include "../inc/utils.h"

#define ACM_CTRL_DTR 0x01
#define ACM_CTRL_RTS 0x02
#define EP_IN_ADDR 0x81
#define EP_OUT_ADDR 0x01

int main(int argc, char** argv) {
  __uint16_t vid = 0;
  __uint16_t pid = 0;

  status_t stat = parseArgs(argc, argv, &vid, &pid);

  if (stat == UTILS_ERROR) {
    fprintf(stderr, "Error parsing arguments.\n");
    exit(1);
  }

  fprintf(stdout, "looking for USB device with vendor id 0x%x and product id 0x%x\n", vid, pid);

  int res = libusb_init(NULL);

  if (res !=0) {
    fprintf(stdout, "error initializing libusb %s\n", libusb_error_name(res));
  }

  libusb_device_handle* devHndl = libusb_open_device_with_vid_pid(NULL, vid, pid);

  if (devHndl == NULL) {
    fprintf(stdout, "could not find device\n");
    libusb_exit(NULL);
    exit(1);
  }

  libusb_device* dev = libusb_get_device(devHndl);

  struct libusb_config_descriptor* conf;

  res = libusb_get_active_config_descriptor(dev, &conf);

  for (int if_num = 0; if_num < conf->bNumInterfaces; if_num++) {
    if (libusb_kernel_driver_active(devHndl, if_num)) {
      libusb_detach_kernel_driver(devHndl, if_num);
    }
    
    res = libusb_claim_interface(devHndl, if_num);

    if (res < 0) {
      fprintf(stderr, "Error claiming interface: %s\n", libusb_error_name(res));
      libusb_free_config_descriptor(conf);
      libusb_exit(NULL);
      exit(1);
    }
  }

  res = libusb_control_transfer(devHndl, 0x21, 0x22, ACM_CTRL_DTR | ACM_CTRL_RTS, 0, NULL, 0, 0);

  if (res < 0) {
    fprintf(stderr, "Error in control transfer: %s\n", libusb_error_name(res));
  }

  unsigned char encoding[] = { 0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08 };
  res = libusb_control_transfer(devHndl, 0x21, 0x20, 0, 0, encoding, sizeof(encoding), 0);
  
  if (res < 0) {
    fprintf(stderr, "Error during control transfer: %s\n", libusb_error_name(res));
  }

  unsigned char buf[65];
  int len;

  while(1) {
    res = libusb_bulk_transfer(devHndl, EP_IN_ADDR, buf, 64, &len, 1000);

    if (res == 0) {
      buf[len] = 0;
      fprintf(stdout, "Received: \"%s\"\n", buf);
    }

    sleep(1);
  }

  for (int if_num = 0; if_num < conf->bNumInterfaces; if_num++) {
    libusb_release_interface(devHndl, if_num);
  }

  if (devHndl) {
    libusb_close(devHndl);
  }
  
  libusb_free_config_descriptor(conf);
  libusb_exit(NULL);
  exit(0);
}
