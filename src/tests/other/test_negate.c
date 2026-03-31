#include <check.h>
#include <stdio.h>
#include <stdint.h>

#include "../../s21_decimal.h"
#include "../../helpers/s21_helpers.h"

#define TEST_OK 0

static void assert_negate(s21_decimal dec_test, s21_decimal dec_check) {
  s21_decimal result;

  int code = s21_negate(dec_test, &result);
  int sign_check = s21_get_sign(dec_check);
  int sign_res = s21_get_sign(result);

  #if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(dec_test);
  printf("\ncheck:\n");
  s21_print_decimal_bits(dec_check);
  printf("sign = %d\n", s21_get_sign;
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  printf("sign = %d\n", sign_result);
  printf("---------------------------------\n\n\n\n");
  #endif

  ck_assert_int_eq(code, TEST_OK);
  ck_assert_int_eq(s21_is_equal(result, dec_check), 1);
  ck_assert_int_eq(sign_check, sign_res);
}

START_TEST(test_negate_1) {
    // 79228162514264337593543950335
    s21_decimal dec_test = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162514264337593543950335
    s21_decimal dec_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    assert_negate(dec_test, dec_check);
}
END_TEST

START_TEST(test_negate_2) {
    // -79228162514264337593543950335
    s21_decimal dec_test = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // 79228162514264337593543950335
    s21_decimal dec_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    assert_negate(dec_test, dec_check);
}
END_TEST

START_TEST(test_negate_3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // -7922816251426433759354395033.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 7922816251426433759354395033.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_5) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // -792281.62514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_6) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // 792281.62514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};

    assert_negate(decimal, decimal_check);
}
END_TEST


START_TEST(test_negate_7) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_8) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_9) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    // -0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80010000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_10) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    // 0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x10000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_11) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_12) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_13) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    // 0.0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x10000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

START_TEST(test_negate_14) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    // -0.0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80010000}};

    assert_negate(decimal, decimal_check);
}
END_TEST

Suite* s21_negate_test(void) {
  Suite* suite = suite_create("s21_negate_test");
  TCase* tc_core = tcase_create("core");
  tcase_set_timeout(tc_core, 30);

  tcase_add_test(tc_core, test_negate_1);
  tcase_add_test(tc_core, test_negate_2);
  tcase_add_test(tc_core, test_negate_3);
  tcase_add_test(tc_core, test_negate_4);
  tcase_add_test(tc_core, test_negate_5);
  tcase_add_test(tc_core, test_negate_6);
  tcase_add_test(tc_core, test_negate_7);
  tcase_add_test(tc_core, test_negate_8);
  tcase_add_test(tc_core, test_negate_9);
  tcase_add_test(tc_core, test_negate_10);
  tcase_add_test(tc_core, test_negate_11);
  tcase_add_test(tc_core, test_negate_12);
  tcase_add_test(tc_core, test_negate_13);
  tcase_add_test(tc_core, test_negate_14);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main(void) {
  Suite* suite = s21_negate_test();
  SRunner* runner = srunner_create(suite);
  // srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? 0 : 1;
}