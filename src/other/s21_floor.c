#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int fl_finish = 0;
  if (!result)
    fl_finish = 1;
  else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    int value_scale = s21_get_scale(value);
    if (!s21_get_sign(value)) {
      result->bits[2] = result->bits[2] >> value_scale;
      result->bits[2] = result->bits[2] << value_scale;
    } else {
      if (value_scale) {
        big_decimal tmp;
        s21_expand(value, &tmp);
        s21_add_1(&tmp);
        s21_normalize(tmp, &result);
        result->bits[2] = result->bits[2] >> (value_scale - 1);
        result->bits[2] = result->bits[2] << (value_scale - 1);
      }
    }
  }
  return fl_finish;
}