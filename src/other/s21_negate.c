#include "../s21_decimal.h"
#include "../helpers/s21_helpers.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    int fl_finish = 0;
    if (!result) fl_finish = 1;
    else {
        for (int i = 0; i < 4; i++) {
            result->bits[i] = value.bits[i];
        }
        result->bits[3] ^= MINUS;
    }
    return fl_finish;
}