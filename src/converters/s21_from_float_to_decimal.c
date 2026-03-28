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
  for (; pt > sx; pt--) {
    
  }
}