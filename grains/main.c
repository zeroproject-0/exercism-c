#include <math.h>
#include <stdint.h>
#include <stdio.h>

uint64_t square(uint8_t index) { return (uint64_t)powl(2, index - 1); }

uint64_t total(void) {
  int chess = 8 * 8;
  return (uint64_t)powl(2, chess + 1) - 1;
}

int main(int argc, char *argv[]) {
  uint8_t i = 64;

  printf("Index %d: %lu\n", i, square(i));

  printf("Total: %lu\n", total());

  return 0;
}
