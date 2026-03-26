#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include <limits.h>

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return 1;
  *dst = 0;

  s21_truncate(src, &src);
  if (src.bits[1] || src.bits[2] || src.bits[0] >> 31) return 1;
  if (s21_get_sign(src)) {
    if (src.bits[0] > INT32_MAX + 1) return 1;
    *dst -= src.bits[0];
  } else {
    if (src.bits[0] > INT32_MAX) return 1;
    *dst = src.bits[0];
  }

  return 0;
}