#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_is_greater(s21_decimal left, s21_decimal right) {
  int res = 0;
  if (s21_is_less(right, left))
    res = 1;
  return res;
}