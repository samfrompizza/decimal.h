#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include <stdint.h>

#include "../s21_decimal.h"

#define MINUS 0x80000000
#define SC 0x00ff0000
#define MAX4BITE 0xffffffff
#define S21_MAX_DECIMAL_LD 79228162514264337593543950335.0L
#define S21_MIN_FLOAT_DECIMAL_LD 1e-28L
#define BUF 128

typedef struct {
  uint64_t bits[7];
  int scale;
  uint16_t sign;
} big_decimal;

static inline int s21_get_sign(s21_decimal dec) { return dec.bits[3] & MINUS; }

static inline void s21_set_sign(s21_decimal *dec) { dec->bits[3] |= MINUS; }

static inline int s21_is_zero(s21_decimal dec) {
  return (dec.bits[0] | dec.bits[1] | dec.bits[2]) == 0;
}

static inline int s21_get_scale(s21_decimal v) {
  return (v.bits[3] & SC) >> 16;
}

static inline void s21_set_scale(s21_decimal *v, int scale) {
  v->bits[3] &= ~SC;
  v->bits[3] |= (scale << 16);
}

static inline int s21_larger_than_96(big_decimal src) {
  return (src.bits[3] | src.bits[4] | src.bits[5] | src.bits[6]) != 0;
}

int s21_cmp_abs_without_scale(big_decimal left, big_decimal right);
void s21_align_scale(big_decimal *left, big_decimal *right);
int s21_normalize(big_decimal src, s21_decimal *dst);
void s21_expand(s21_decimal src, big_decimal *dst);

void s21_multiply_by_10(big_decimal *v);
uint32_t s21_div_by_10(big_decimal *v);
void s21_add_1(big_decimal *v);

#endif