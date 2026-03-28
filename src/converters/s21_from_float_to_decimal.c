#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return 1;
  if (isnan(src) || isinf(src)) return 1;

  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }

  long double x = (long double)src;
  long double ax = fabsl(x);

  if (src == 0) return 0;
  if (ax > 0.0L && ax < S21_MIN_FLOAT_DECIMAL_LD) return 1;
  if (ax > S21_MAX_DECIMAL_LD) return 1;

  dst->bits[3] = src < 0 ? MINUS : 0;

  char sx[BUF];
  sprintf(sx, ".7g", ax);

  char *pt = strchr(sx, 'e');
  if (pt == NULL) pt = sx + strlen(sx);
  int n = 0;
  for (; pt > sx; pt--) {
    if (*pt == '.') pt --;
    s21_decimal tmp;
    big_decimal big_tmp;
    int num = *pt - '0';
    s21_from_int_to_decimal(num, &tmp);
    s21_expand(tmp, &big_tmp);
    for (int i = 0; i < n; i++) s21_multiply_by_10(&big_tmp);
    n++;
    s21_normalize(big_tmp, &tmp);
    s21_add(tmp, *dst, dst);
  }

  if (*pt == 'e') {
    int scale = (*(pt + 2) - '0') * 10 + *(pt + 3) - '0';
    dst->bits[3] |= scale << 15;
  }

  return 0;
}