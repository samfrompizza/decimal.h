#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "../s21_decimal.h"

#include <stdint.h>

#define MINUS 0x80000000
#define SC 0x00ff0000
#define MAX4BITE 0xffffffff

typedef struct {
  uint64_t bits[7];
  uint16_t scale;
  uint16_t sign;
} big_decimal;

static inline int s21_get_sign(s21_decimal dec) {
  return dec.bits[3] & MINUS;
}

static inline void s21_set_sign(s21_decimal *dec) {
  dec->bits[3] |= MINUS;
}

static inline int s21_is_zero(s21_decimal dec) {
  return dec.bits[0] ? 0 : (dec.bits[1] ? 0 : (dec.bits[2] ? 0 : 1));
}

int s21_cmp_abs_withot_scale(s21_decimal left, s21_decimal right);
void s21_align_scale(s21_decimal left, s21_decimal right);
void s21_normalize(big_decimal src, s21_decimal res);

#endif