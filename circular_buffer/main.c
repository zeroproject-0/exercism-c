#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int buffer_value_t;

typedef struct {
  int start;
  int end;
  int count;
  size_t capacity;
  buffer_value_t *values;
} circular_buffer_t;

void print_buff(circular_buffer_t *buffer) {
  printf("capacity: %zu\n", buffer->capacity);
  printf("count: %d\n", buffer->count);
  printf("start: %d\n", buffer->start);
  printf("end: %d\n", buffer->end);
  for (size_t i = 0; i < buffer->capacity; i++) {
    printf("ITEM %zu: %d\n", i, buffer->values[i]);
  }
}

circular_buffer_t *new_circular_buffer(size_t capacity) {
  circular_buffer_t *cb =
      (circular_buffer_t *)malloc(sizeof(circular_buffer_t));

  cb->start = 0;
  cb->end = 0;
  cb->count = 0;
  cb->capacity = capacity;
  cb->values = (buffer_value_t *)malloc(capacity * sizeof(buffer_value_t));

  memset(cb->values, -1, capacity * sizeof(buffer_value_t));

  return cb;
}

void delete_buffer(circular_buffer_t *buffer) { free(buffer); }

void clear_buffer(circular_buffer_t *buffer) {
  buffer->count = 0;
  buffer->start = 0;
  buffer->end = 0;
  memset(buffer->values, -1, buffer->capacity);
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *value) {
  if (buffer->count == 0) {
    errno = 61;
    return EXIT_FAILURE;
  }

  *value = buffer->values[buffer->start++];
  buffer->start %= buffer->capacity;
  buffer->count--;

  return EXIT_SUCCESS;
}

int16_t write(circular_buffer_t *buffer, buffer_value_t value) {
  if (buffer->count == buffer->capacity) {
    errno = 105;
    return EXIT_FAILURE;
  }

  buffer->values[buffer->end++] = value;
  buffer->end %= buffer->capacity;
  buffer->count++;

  return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value) {
  if (buffer->start == buffer->end) {
    buffer->start++;
    buffer->start %= buffer->capacity;
  }

  if (buffer->count == buffer->capacity)
    buffer->count--;

  return write(buffer, value);
}

#define MAX_ERROR_MSG_LEN 100
#define ARRAY_LENGTH(A) (sizeof(A) / sizeof(A[0]))

void write_values_to_buffer(size_t length, buffer_value_t values[],
                            bool writeover, circular_buffer_t *buffer) {
  for (size_t i = 0; i < length; ++i) {
    int16_t status = 0;
    if (!writeover)
      status = write(buffer, values[i]);
    else
      status = overwrite(buffer, values[i]);
    char error_message[MAX_ERROR_MSG_LEN] = {0};
    snprintf(error_message, MAX_ERROR_MSG_LEN,
             "Writing %d at %zu resulted in errno %d", values[i], i, errno);
    printf("%d == %d: %s\n", EXIT_SUCCESS, status, error_message);
  }
}

static void read_values_from_buffer(size_t length, buffer_value_t values[],
                                    circular_buffer_t *buffer) {
  for (size_t i = 0; i < length; ++i) {
    buffer_value_t read_value = 0;
    int16_t status = read(buffer, &read_value);
    char error_message[MAX_ERROR_MSG_LEN] = {0};
    snprintf(error_message, MAX_ERROR_MSG_LEN,
             "Reading at %zu resulted in errno %d, expected to read %d", i,
             errno, values[i]);
    printf("%d == %d: %s\n", EXIT_SUCCESS, status, error_message);
    snprintf(error_message, MAX_ERROR_MSG_LEN,
             "Read %d at %zu where %d was expected", read_value, i, values[i]);
    printf("%d == %d: %s\n", values[i], read_value, error_message);
  }
}

void test_reading_empty_buffer_fails(void) {
  printf("\ntest_reading_empty_buffer_fails\n");
  size_t capacity = 1;
  buffer_value_t read_value = 0;
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  int16_t status = read(buffer, &read_value);
  printf("STATUS: %d == %d\n", EXIT_FAILURE, status);
  printf("ERRORNO: %d == %d\n", ENODATA, errno);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

void test_can_read_item_just_written(void) {
  printf("\ntest_can_read_item_just_written\n");
  size_t capacity = 1;
  buffer_value_t values[] = {1};
  size_t values_length = ARRAY_LENGTH(values);
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  write_values_to_buffer(values_length, values, false, buffer);
  // print_buff(buffer);
  read_values_from_buffer(values_length, values, buffer);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

void test_each_item_may_only_be_read_once(void) {
  printf("\ntest_each_item_may_only_be_read_once\n");
  size_t capacity = 1;
  buffer_value_t values[] = {1};
  size_t values_length = ARRAY_LENGTH(values);
  buffer_value_t read_value = 0;
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  write_values_to_buffer(values_length, values, false, buffer);
  read_values_from_buffer(values_length, values, buffer);
  // print_buff(buffer);
  int16_t status = read(buffer, &read_value);
  printf("STATUS: %d == %d\n", EXIT_FAILURE, status);
  printf("ERRORNO: %d == %d\n", ENODATA, errno);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

void test_read_frees_capacity_for_another_write(void) {
  printf("\ntest_read_frees_capacity_for_another_write\n");
  size_t capacity = 1;
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  write_values_to_buffer(1, (buffer_value_t[]){1}, false, buffer);
  print_buff(buffer);
  read_values_from_buffer(1, (buffer_value_t[]){1}, buffer);

  print_buff(buffer);
  write_values_to_buffer(1, (buffer_value_t[]){2}, false, buffer);
  print_buff(buffer);
  read_values_from_buffer(1, (buffer_value_t[]){2}, buffer);
  print_buff(buffer);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

void test_overwrite_acts_like_write_on_non_full_buffer(void) {
  printf("\ntest_overwrite_acts_like_write_on_non_full_buffer\n");
  size_t capacity = 2;
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  write_values_to_buffer(1, (buffer_value_t[]){1}, false, buffer);
  write_values_to_buffer(1, (buffer_value_t[]){2}, true, buffer);
  read_values_from_buffer(2, (buffer_value_t[]){1, 2}, buffer);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

void test_overwrite_replaces_oldest_item_on_full_buffer(void) {
  printf("\ntest_overwrite_replaces_oldest_item_on_full_buffer\n");
  size_t capacity = 2;
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  write_values_to_buffer(2, (buffer_value_t[]){1, 2}, false, buffer);
  write_values_to_buffer(1, (buffer_value_t[]){3}, true, buffer);
  read_values_from_buffer(2, (buffer_value_t[]){2, 3}, buffer);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

void test_overwrite_replaces_oldest_item_remaining_following_read(void) {
  printf("\ntest_overwrite_replaces_oldest_item_remaining_following_read\n");
  size_t capacity = 3;
  circular_buffer_t *buffer = new_circular_buffer(capacity);
  write_values_to_buffer(3, (buffer_value_t[]){1, 2, 3}, false, buffer);
  read_values_from_buffer(1, (buffer_value_t[]){1}, buffer);
  write_values_to_buffer(1, (buffer_value_t[]){4}, false, buffer);
  write_values_to_buffer(1, (buffer_value_t[]){5}, true, buffer);
  read_values_from_buffer(3, (buffer_value_t[]){3, 4, 5}, buffer);
  delete_buffer(buffer);
  printf("----------------------------------------\n");
}

int main(int argc, char *argv[]) {
  printf("Circular Buffer\n");

  // size_t capacity = 3;
  // buffer_value_t write_value = 14;
  // circular_buffer_t *buffer = new_circular_buffer(capacity);
  // int16_t status = write(buffer, write_value);
  // buffer_value_t read_value = 0;
  // int16_t statusR = read(buffer, &read_value);
  // printf("STATUS: %d\n", status);
  // printf("STATUSR: %d\n", statusR);
  // printf("value %d \n", read_value);

  // for (size_t i = 0; i < buffer->capacity; i++) {
  //   printf("ITEM %zu: %d\n", i, buffer->values[i]);
  // }

  test_reading_empty_buffer_fails();
  test_can_read_item_just_written();
  test_each_item_may_only_be_read_once();
  test_read_frees_capacity_for_another_write();
  test_overwrite_acts_like_write_on_non_full_buffer();
  test_overwrite_replaces_oldest_item_on_full_buffer();
  test_overwrite_replaces_oldest_item_remaining_following_read();

  return EXIT_SUCCESS;
}
