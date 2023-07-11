#include <stdio.h>

int square_root(unsigned int n) {
  for (int i = 0; i < n; ++i) {
    if (i * i == n)
      return i;
  }
  return 1;
}

int main(void) {
  int n = 25;

  printf("N: %d\n", n);
  printf("Sqrt: %d\n", square_root(n));

  return 0;
}
