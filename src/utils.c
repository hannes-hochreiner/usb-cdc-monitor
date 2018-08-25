#include "../inc/utils.h"

status_t parseArgs(int argc, char** argv, __uint16_t* vendorId, __uint16_t* productId) {
  if (argc != 5) {
    return UTILS_ERROR;
  }

  for (int cntr = 1; cntr < argc; cntr += 2) {
    if (strcmp(argv[cntr], "-vid") == 0) {
      *vendorId = strtol(argv[cntr + 1], NULL, 16);
    } else if (strcmp(argv[cntr], "-pid") == 0) {
      *productId = strtol(argv[cntr + 1], NULL, 16);
    }
  }

  return UTILS_OK;
}
