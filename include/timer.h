#pragma once
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ctime>

#include "error.h"

static double dtime() {
  struct timespec tp;
  int err = clock_gettime(CLOCK_REALTIME, &tp);
  if (err != 0) {
    printf("clock_gettime(CLOCK_REALTIME, ...) failed");
    return 0.0;
  }
  return static_cast<double>(tp.tv_sec) + tp.tv_nsec * 1.e-9;
}
