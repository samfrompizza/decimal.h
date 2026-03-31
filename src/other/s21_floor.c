#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int fl_finish = 0;
  if (!result)
    fl_finish = 1;

  else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }

    if (s21_get_scale(value) == 0) {
      *result = value;
    } else {
      int rem = 0;
      big_decimal tmp;
      s21_expand(value, &tmp);

      int add = 0;
      while (tmp.scale > 0) {
        rem = s21_div_by_10(&tmp);
        if (rem != 0) {
          add++;
        }
        tmp.scale--;
      }

      if (tmp.sign != 0 && add != 0) {
        s21_add_1(&tmp);
      }

      result->bits[0] = (uint32_t)tmp.bits[0];
      result->bits[1] = (uint32_t)tmp.bits[1];
      result->bits[2] = (uint32_t)tmp.bits[2];
      if (tmp.sign) {
        s21_set_sign(result);
      }
      s21_truncate(*result, result);
    }
  }

  return fl_finish;
}