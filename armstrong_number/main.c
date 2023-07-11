#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool is_armstrong_number(int candidate) {
  int base = 10, res = 0;
  int k = log10(candidate) + 1;

  for (int i = 0; i < k; ++i) {
    int bi = (int)pow(base, i);
    int di = ((candidate % (int)pow(base, i + 1)) - (candidate % bi)) / bi;
    res += (int)pow(di, k);
  }

  return res == candidate;
}

int main(void) {
  int n = 9926315;
  printf("%d => %s\n", n, is_armstrong_number(n) ? "True" : "False");

  return 0;
}
