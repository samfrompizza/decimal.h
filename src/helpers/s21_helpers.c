#include "s21_helpers.h"

int s21_cmp_abs_without_scale(big_decimal left, big_decimal right) {
  int result = 0;
  for (int i = 6; i >= 0; --i) {
    if (left.bits[i] != right.bits[i]) {
      result = (left.bits[i] > right.bits[i]) ? 1 : -1;
      break;
    }
  }
  return result;
}

void s21_align_scale(big_decimal *left, big_decimal *right) {
  if (left->scale < right->scale) {
    int scale_diff = right->scale - left->scale;
    for (int i = 0; i < scale_diff; i++) {
      s21_multiply_by_10(left);
    }
    left->scale = right->scale;
  } else {
    int scale_diff = left->scale - right->scale;
    for (int i = 0; i < scale_diff; i++) {
      s21_multiply_by_10(right);
    }
    right->scale = left->scale;
  }
}

int s21_normalize(big_decimal src, s21_decimal *dst) {
  int res = 0;
  int rem = 0;
  int nums_fl = 0;
  while (s21_larger_than_96(src) || src.scale > 28) {
    if (rem > 0) {
      nums_fl = 1;
    }
    rem = s21_div_by_10(&src);
    src.scale--;
  }
  if ((rem > 5) || (rem == 5 && nums_fl == 1) ||
      (rem == 5 && nums_fl == 0 && (src.bits[0] & 1))) {
    s21_add_1(&src);
    if (s21_larger_than_96(src)) {
      rem = s21_div_by_10(&src);
      src.scale--;
    }
  }
  if (src.scale < 0) {
    if (src.sign)
      res = 2;
    else
      res = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    dst->bits[0] = (uint32_t)src.bits[0];
    dst->bits[1] = (uint32_t)src.bits[1];
    dst->bits[2] = (uint32_t)src.bits[2];
    s21_set_scale(dst, src.scale);
    if (src.sign == 1) {
      s21_set_sign(dst);
    }
  }
  return res;
}

void s21_expand(s21_decimal src, big_decimal *dst) {
  if (dst) {
    for (int i = 0; i < 7; ++i) {
      dst->bits[i] = 0;
    }
    dst->bits[0] = (uint32_t)src.bits[0];
    dst->bits[1] = (uint32_t)src.bits[1];
    dst->bits[2] = (uint32_t)src.bits[2];
    dst->scale = s21_get_scale(src);
    dst->sign = s21_get_sign(src) ? 1 : 0;
  }
}

void s21_multiply_by_10(big_decimal *v) {
  uint64_t carry = 0;
  for (int i = 0; i < 7; i++) {
    uint64_t res = (v->bits[i] * 10) + carry;
    v->bits[i] = res & MAX4BITE;
    carry = res >> 32;
  }
}

uint32_t s21_div_by_10(big_decimal *v) {
  uint64_t rem = 0;
  for (int i = 6; i >= 0; i--) {
    uint64_t current = v->bits[i] + (rem << 32);
    v->bits[i] = current / 10;
    rem = current % 10;
  }
  return (uint32_t)rem;
}

void s21_add_1(big_decimal *v) {
  uint64_t carry = 1;
  for (int i = 0; i < 7 && carry; i++) {
    uint64_t res = v->bits[i] + carry;
    v->bits[i] = res & MAX4BITE;
    carry = res >> 32;
  }
}