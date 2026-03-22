#include "s21_helpers.h"

int s21_cmp_abs_withot_scale(s21_decimal left, s21_decimal right) {
    int result = 0;
    for (int i = 2; i >= 0; --i) {
        if (left.bits[i] != right.bits[i]) {
            result = (left.bits[i] > right.bits[i]) ? -1 : 1;
            break;
        }
    }
    return result;
}

