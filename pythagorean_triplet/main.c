#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint16_t a;
  uint16_t b;
  uint16_t c;
} triplet_t;

typedef struct {
  size_t count;
  triplet_t *triplets;
} triplets_t;

void free_triplets(triplets_t *t) {
  free(t->triplets);
  free(t);
}

triplets_t *triplets_with_sum(uint16_t e) {
  triplet_t *t = calloc(100, sizeof(triplet_t));
  size_t size_arr = 0;

  for (uint16_t a = 3; a <= (e - 3) / 3; ++a) {
    for (uint16_t b = (a + 1); b <= (e - 1 - a) / 2; ++b) {
      uint16_t c = e - a - b;
      if (a * a + b * b == c * c)
        t[size_arr++] = (triplet_t){a, b, c};
    }
  }

  triplets_t *ts =
      (triplets_t *)malloc(sizeof(triplets_t) + size_arr * sizeof(triplet_t));

  ts->count = size_arr;
  ts->triplets = realloc(t, size_arr * sizeof(triplet_t));

  return ts;
}

int main(int argc, char *argv[]) {
  printf("Pythagorena Triplet\n");

  triplets_t *t = triplets_with_sum(12);
  printf("%zu\n", t->count);
  for (size_t i = 0; i < t->count; ++i) {
    printf("%zu) %d + %d = %d\n", i + 1, t->triplets[i].a, t->triplets[i].b,
           t->triplets[i].c);
  }
  free_triplets(t);

  return EXIT_SUCCESS;
}
