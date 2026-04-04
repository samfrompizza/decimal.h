#include <limits.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return 1;

  for (int i = 0; i < 4; ++i) dst->bits[i] = 0;

  if (src < 0) {
    dst->bits[3] = MINUS;
    dst->bits[0] = (uint32_t)(-(int64_t)src);
  } else {
    dst->bits[0] = (uint32_t)src;
  }

  return 0;
}