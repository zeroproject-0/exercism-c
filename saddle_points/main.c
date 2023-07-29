#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint16_t row;
  uint16_t column;
} saddle_point_t;

typedef struct {
  size_t count;
  saddle_point_t *points;
} saddle_points_t;

void print_mat(size_t rows, size_t columns, uint8_t (*mat)[columns]) {
  printf("\n\n Print Mat\n");
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

void free_saddle_points(saddle_points_t *s) { free(s); }

saddle_points_t *saddle_points(uint16_t rows, uint16_t columns,
                               uint8_t (*mat)[columns]) {
  saddle_point_t *points =
      calloc(rows > columns ? rows : columns, sizeof(saddle_point_t));
  size_t len = 0;

  for (uint8_t i = 0; i < rows; i++) {
    for (uint8_t j = 0; j < columns; j++) {
      bool is_valid = true;

      for (uint8_t k = 0; k < columns; k++)
        if (mat[i][j] < mat[i][k]) {
          is_valid = false;
          break;
        }

      for (uint8_t k = 0; k < rows; k++)
        if (mat[i][j] > mat[k][j]) {
          is_valid = false;
          break;
        }

      if (is_valid) {
        points[len++] = (saddle_point_t){.row = i + 1, .column = j + 1};
      }
    }
  }

  size_t size_len = (len * sizeof(saddle_point_t));

  saddle_points_t *res = malloc(sizeof(saddle_points_t) + size_len);
  res->count = len;
  res->points = realloc(points, size_len);

  return res;
}

int main(int argc, char *argv[]) {
  printf("Saddle Points\n");

  uint8_t matrix[2][3] = {{3, 1, 3}, {3, 2, 4}};

  print_mat(2, 3, matrix);

  saddle_points_t *s = saddle_points(2, 3, matrix);

  for (size_t i = 0; i < s->count; i++) {
    printf("[%d,%d]\n", s->points[i].column, s->points[i].row);
  }

  return EXIT_SUCCESS;
}
