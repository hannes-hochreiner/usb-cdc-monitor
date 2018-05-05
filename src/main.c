#include <stdio.h>
#include "../inc/utils.h"

int main(int argc, char** argv) {
  __uint16_t vid = 0;
  __uint16_t pid = 0;

  status_t stat = parseArgs(argc, argv, &vid, &pid);

  if (stat == UTILS_ERROR) {
    fprintf(stderr, "Error parsing arguments.\n");
    exit(1);
  }

  fprintf(stdout, "looking for USB device with vendor id 0x%x and product id 0x%x\n", vid, pid);

  exit(0);
}
