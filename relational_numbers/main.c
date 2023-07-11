#include "./main.h"
#include <stdio.h>
;
void test_add_rational_number_to_additive_inverse(void) {
  printf("\ntest_add_rational_number_to_additive_inverse\n");

  rational_t r1 = {1, 2};
  rational_t r2 = {-1, 2};
  rational_t expected = {0, 1};
  rational_t actual = add(r1, r2);
  r_print("R1: ", r1);
  r_print("R2: ", r2);
  r_print("Expected", expected);
  r_print("Actual", actual);
}

void test_multiply_positive_and_negative_rational_numbers(void) {
  printf("\ntest_multiply_positive_and_negative_rational_numbers\n");
  rational_t r1 = {-1, 2};
  rational_t r2 = {2, 3};
  rational_t expected = {-1, 3};
  rational_t actual = multiply(r1, r2);
  r_print("R1: ", r1);
  r_print("R2: ", r2);
  r_print("Expected", expected);
  r_print("Actual", actual);
}

void test_raise_positive_rational_number_to_negative_integer_power(void) {
  printf("\ntest_raise_positive_rational_number_to_negative_integer_power\n");
  rational_t r = {3, 5};
  int16_t n = -2;
  rational_t expected = {25, 9};
  rational_t actual = exp_rational(r, n);
  r_print("R1: ", r);
  printf("N: %d\n", n);
  r_print("Expected", expected);
  r_print("Actual", actual);
}

int main(int argc, char *argv[]) {
  printf("Relational numbers\n");

  // test_add_rational_number_to_additive_inverse();
  // test_multiply_positive_and_negative_rational_numbers();
  test_raise_positive_rational_number_to_negative_integer_power();
  return EXIT_SUCCESS;
}
