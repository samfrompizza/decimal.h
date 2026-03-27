#include "../s21_decimal.h"
#include "../helpers/s21_helpers.h"

int s21_is_not_equal(s21_decimal left, s21_decimal right) {
    int res = 0;
    if (!s21_is_equal(left,right)) res = 1;
    return res;
}