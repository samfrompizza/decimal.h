#include <math.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) return 1;

  long double value = (long double)src.bits[0] +
                      (long double)src.bits[1] * powl(2, 32) +
                      (long double)src.bits[2] * powl(2, 64);
  value /= powl(10, s21_get_scale(src));
  if (s21_get_sign(src)) value = -value;
  *dst = (float)value;
  if (isnan(*dst) || isinf(*dst)) return 1;

  return 0;
}