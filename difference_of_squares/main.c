#include <stdio.h>

unsigned int sum_of_squares(unsigned int number) {
  return ((number * (number + 1) * (2 * number + 1)) / 6);
}

unsigned int square_of_sum(unsigned int number) {
  unsigned int res = (number * (number + 1) / 2);
  return res * res;
}

unsigned int difference_of_squares(unsigned int number) {
  return (square_of_sum(number) - sum_of_squares(number));
}

int main(void) {
  int n = 10;

  printf("N: %d\n", n);
  printf("Sum of Squares: %d\n", sum_of_squares(n));
  printf("Squares of Sums: %d\n", square_of_sum(n));
  printf("Difference of squares: %d\n", difference_of_squares(n));

  return 0;
}
