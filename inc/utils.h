#ifndef __UTILS_H__
#define __UTILS_H__

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
  UTILS_OK = 0,
  UTILS_ERROR
} status_t;

status_t parseArgs(int argc, char** argv, __uint16_t* vendorId, __uint16_t* productId);

#endif
