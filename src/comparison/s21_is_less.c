#include "../s21_decimal.h"
#include "../helpers/s21_helpers.h"

int s21_is_less(s21_decimal left, s21_decimal right) {
    int res = 1;
    if (s21_is_zero(left) && s21_is_zero(right)) res = 0;
    else {
        int sign_l = s21_get_sign(left);
        int sign_r = s21_get_sign(right);
        if (sign_l > sign_r) res = 0;
        else if (sign_l == sign_r) {
            big_decimal big_left, big_right;
            s21_expand(left, &big_left);
            s21_expand(right, &big_right);
            s21_align_scale(&big_left, &big_right);
            int compare = s21_cmp_abs_without_scale(big_left, big_right);
            if ((compare >= 0 && !big_left.sign) || (compare <= 0 && big_left.sign)) res = 0;
        }
    }
    return res;
}
