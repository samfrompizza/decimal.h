#include <math.h>
#include <stdint.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

static void s21_clear_decimal(s21_decimal *dst) {
  for (int i = 0; i < 4; ++i) {
    dst->bits[i] = 0;
  }
}

static void s21_normalize_to_10(long double *x, int *exp10) {
  while (*x >= 10.0L) {
    *x /= 10.0L;
    ++(*exp10);
  }
  while (*x < 1.0L) {
    *x *= 10.0L;
    --(*exp10);
  }
}

static void s21_collect_digits(long double *x, int dig[8], int *sticky) {
  for (int i = 0; i < 8; ++i) {
    int d = (int)(*x);
    if (d < 0) d = 0;
    if (d > 9) d = 9;

    dig[i] = d;
    *x = (*x - (long double)d) * 10.0L;
  }
  *sticky = (*x > 0.0L);
}

static uint32_t s21_build_mantissa(const int dig[8]) {
  uint32_t mant = 0;
  for (int i = 0; i < 7; ++i) {
    mant = mant * 10u + (uint32_t)dig[i];
  }
  return mant;
}

static void s21_round_mantissa(uint32_t *mant, int guard, int sticky,
                               int *exp10) {
  if (guard > 5 || (guard == 5 && (sticky || (*mant & 1u)))) {
    (*mant)++;
  }

  if (*mant == 10000000u) {
    *mant = 1000000u;
    ++(*exp10);
  }
}

static int s21_apply_exponent_and_scale(s21_decimal *dst, int exp10,
                                        int *scale) {
  if (exp10 >= 6) {
    int k = exp10 - 6;
    for (int i = 0; i < k; ++i) {
      if (s21_mul10_96(dst)) return 1;
    }
    *scale = 0;
  } else {
    *scale = 6 - exp10;
  }
  return 0;
}

static int s21_reduce_scale_if_needed(s21_decimal *dst, int *scale) {
  while (*scale > 28) {
    uint32_t rem = s21_div10_96(dst);
    if (rem > 5 || (rem == 5 && ((uint32_t)dst->bits[0] & 1u))) {
      if (s21_add1_96(dst)) return 1;
    }
    --(*scale);
  }
  return 0;
}

static void s21_strip_trailing_zeros(s21_decimal *dst, int *scale) {
  while (*scale > 0) {
    s21_decimal tmp = *dst;
    uint32_t rem = s21_div10_96(&tmp);
    if (rem != 0) break;
    *dst = tmp;
    --(*scale);
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return 1;

  s21_clear_decimal(dst);

  if (isnan(src) || isinf(src)) return 1;
  if (src == 0.0f) return 0;

  long double x = fabsl((long double)src);

  if (x > 0.0L && x < S21_MIN_FLOAT_DECIMAL_LD) return 1;
  if (x > S21_MAX_DECIMAL_LD) return 1;

  int sign = (src < 0.0f);

  int exp10 = 0;
  s21_normalize_to_10(&x, &exp10);

  int dig[8] = {0};
  int sticky = 0;
  s21_collect_digits(&x, dig, &sticky);

  uint32_t mant = s21_build_mantissa(dig);
  int guard = dig[7];

  s21_round_mantissa(&mant, guard, sticky, &exp10);

  dst->bits[0] = (int)mant;

  int scale = 0;
  if (s21_apply_exponent_and_scale(dst, exp10, &scale)) return 1;
  if (s21_reduce_scale_if_needed(dst, &scale)) return 1;

  s21_strip_trailing_zeros(dst, &scale);

  s21_set_scale(dst, scale);
  if (sign) s21_set_sign(dst);

  return 0;
}