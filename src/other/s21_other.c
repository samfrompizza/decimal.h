#include "../s21_decimal.h"
#include "../helpers/s21_helpers.h"

int s21_round(s21_decimal value, s21_decimal *result) {

}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int fl_finish = 0;
    if (!result) fl_finish = 1;
    else {
        for (int i = 0; i < 4; i++) {
            result->bits[i] = 0;
        }
        int value_scale = s21_get_scale(value);
        if (value_scale == 0) *result = value;
        else {
            big_decimal big_value;
            s21_expand(value, &big_value);
            while (big_value.scale > 0) {
                s21_div_by_10(&big_value);
                big_value.scale--;
            }

            result->bits[0] = (uint32_t)big_value.bits[0];
            result->bits[1] = (uint32_t)big_value.bits[1];
            result->bits[2] = (uint32_t)big_value.bits[2];
            if (big_value.sign) {
                s21_set_sign(result);
            }
        }
    }
    return fl_finish;
}