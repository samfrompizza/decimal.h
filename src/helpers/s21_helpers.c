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
    if (rem > 0 || nums_fl) {
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
  if (src.scale < 0 || s21_larger_than_96(src)) {
    if (src.sign)
      res = 2;
    else
      res = 1;
  } else if (s21_is_zero_big(src) && (rem > 0 || nums_fl)) {
    res = 2;
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

int s21_mul10_96(s21_decimal *d) {
  uint64_t carry = 0;
  for (int i = 0; i < 3; ++i) {
    uint64_t cur = (uint64_t)(uint32_t)d->bits[i] * 10u + carry;
    d->bits[i] = (int)(cur & 0xFFFFFFFFu);
    carry = cur >> 32;
  }
  return carry != 0;
}

uint32_t s21_div10_96(s21_decimal *d) {
  uint64_t rem = 0;
  for (int i = 2; i >= 0; --i) {
    uint64_t cur = (rem << 32) | (uint32_t)d->bits[i];
    d->bits[i] = (int)(cur / 10u);
    rem = cur % 10u;
  }
  return (uint32_t)rem;
}

int s21_add1_96(s21_decimal *d) {
  uint64_t carry = 1;
  for (int i = 0; i < 3 && carry; ++i) {
    uint64_t cur = (uint64_t)(uint32_t)d->bits[i] + carry;
    d->bits[i] = (int)(cur & 0xFFFFFFFFu);
    carry = cur >> 32;
  }
  return carry != 0;
}

void s21_shift_left(big_decimal *dec) {
  int carry = 0;
  for (int i = 0; i < 7; i++) {
    uint64_t tmp = dec->bits[i] << 1;
    tmp |= carry;
    dec->bits[i] = tmp & MAX4BITE;
    carry = (tmp >> 32) != 0;
  }
}

void s21_add_mantissa(big_decimal value_1, big_decimal value_2,
                      big_decimal *result) {
  uint64_t carry = 0;
  for (int i = 0; i < 7; i++) result->bits[i] = 0;
  for (int i = 0; i < 7; i++) {
    uint64_t big_sum = value_1.bits[i] + value_2.bits[i] + carry;
    result->bits[i] = big_sum & MAX4BITE;
    carry = big_sum >> 32;
  }
}

void s21_sub_mantissa(big_decimal value_1, big_decimal value_2,
                      big_decimal *result) {
  int borrow = 0;
  for (int i = 0; i < 7; i++) result->bits[i] = 0;
  for (int i = 0; i < 7; i++) {
    int64_t diff = (int64_t)value_1.bits[i] - (int64_t)value_2.bits[i] - borrow;
    if (diff < 0) {
      diff += (1LL << 32);
      borrow = 1;
    } else
      borrow = 0;
    result->bits[i] = diff & MAX4BITE;
  }
}

void s21_mul_mantissa(big_decimal value_1, big_decimal value_2,
                      big_decimal *result) {
  for (int i = 0; i < 7; i++) result->bits[i] = 0;
  for (int i = 0; i < 7; i++) {
    uint64_t carry = 0;
    for (int j = 0; j < 7 - i; j++) {
      uint64_t mul = (uint64_t)value_1.bits[i] * (uint64_t)value_2.bits[j] +
                     result->bits[i + j] + carry;
      result->bits[i + j] = mul & MAX4BITE;
      carry = mul >> 32;
    }
  }
}

void s21_div_mantissa(big_decimal value_1, big_decimal value_2,
                      big_decimal *result, big_decimal *remainder) {
  for (int i = 0; i < 7; i++) {
    result->bits[i] = 0;
    remainder->bits[i] = 0;
  }

  for (int i = 223; i >= 0; i--) {
    s21_shift_left(remainder);
    int block_index = i / 32;
    int bit_index = i % 32;
    int bit = (value_1.bits[block_index] >> bit_index) & 1;
    if (bit) {
      remainder->bits[0] |= 1;
    }
    if (s21_cmp_abs_without_scale(*remainder, value_2) >= 0) {
      big_decimal tmp_remainder;
      s21_sub_mantissa(*remainder, value_2, &tmp_remainder);
      *remainder = tmp_remainder;
      result->bits[block_index] |= (1ULL << bit_index);
    }
  }
}

void s21_print_decimal_bits(s21_decimal dec) {
  printf("Decimal bits: %x %x %x %x", dec.bits[0], dec.bits[1], dec.bits[2],
         dec.bits[3]);
}