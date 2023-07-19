#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  BLACK = 0,
  BROWN = 1,
  RED = 2,
  ORANGE = 3,
  YELLOW = 4,
  GREEN = 5,
  BLUE = 6,
  VIOLET = 7,
  GREY = 8,
  WHITE = 9,
} resistor_band_t;

uint16_t color_code(resistor_band_t color) { return (uint16_t)color; }

resistor_band_t *colors() {
  static resistor_band_t color_array[] = {BLACK, BROWN, RED,    ORANGE, YELLOW,
                                          GREEN, BLUE,  VIOLET, GREY,   WHITE};
  resistor_band_t *colors = malloc(sizeof(color_array));
  memcpy(colors, color_array, sizeof(color_array));
  return colors;
}

int main(int argc, char *argv[]) {
  printf("Resistor color\n");
  return EXIT_SUCCESS;
}
