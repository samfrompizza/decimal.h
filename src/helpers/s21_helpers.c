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

void s21_expand(s21_decimal src, big_decimal *dst) {
    if (!dst) return;

    for (int i = 0; i < 7; ++i) {
        dst->bits[i] = 0;
    }

    dst->bits[0] = (uint32_t)src.bits[0];
    dst->bits[1] = (uint32_t)src.bits[1];
    dst->bits[2] = (uint32_t)src.bits[2];

    dst->scale = (uint16_t)s21_get_scale(src);
    dst->sign = (uint16_t)s21_get_sign(src);
}