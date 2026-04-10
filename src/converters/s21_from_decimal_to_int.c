#include <limits.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst)
    return 1;

  *dst = 0;
  s21_truncate(src, &src);

  if (src.bits[1] != 0 || src.bits[2] != 0)
    return 1;

  uint32_t tmp = (uint32_t)src.bits[0];
  int sign = s21_get_sign(src) != 0;

  if (!sign) {
    if (tmp > (uint32_t)INT_MAX)
      return 1;
    *dst = (int)tmp;
  } else {
    if (tmp > ((uint32_t)INT_MAX + 1u))
      return 1;
    if (tmp == ((uint32_t)INT_MAX + 1u))
      *dst = INT_MIN;
    else
      *dst = -(int)tmp;
  }

  return 0;
}