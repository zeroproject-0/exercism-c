#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int *binary_search_impl(int value, const int *arr, size_t length,
                              int start, int end) {

  int mid = (start + end) / 2;
  printf("V: %d L: %zu M: %d S: %d E: %d ARR_MID: %d \n", value, length, mid,
         start, end, arr[mid]);
  if (arr[mid] == value)
    return &arr[mid];
  if (mid <= 0 || start - end == 1)
    return NULL;

  if (arr[mid] > value)
    return binary_search_impl(value, arr, length, start, mid - 1);

  return binary_search_impl(value, arr, length, mid + 1, end);
}

const int *binary_search(int value, const int *arr, size_t length) {
  if (length == 0)
    return NULL;
  for (size_t i = 0; i < length; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return binary_search_impl(value, arr, length, 0, length - 1);
}

char *parse_bool(int p) { return p == 0 ? "FALSE" : "TRUE"; }

void test_a_value_in_the_middle_of_an_array(void) {
  printf("test_a_value_in_the_middle_of_an_array:\n");
  int arr[] = {1, 3, 4, 6, 8, 9, 11};
  size_t length = sizeof(arr) / sizeof(arr[0]);
  int idx = 3, elem = 6;
  printf("%d == %d: %s\n", arr[idx], *binary_search(elem, arr, length),
         parse_bool(&arr[idx] == binary_search(elem, arr, length)));
}

void test_finds_a_value_in_an_array_of_odd_length(void) {
  printf("test_finds_a_value_in_an_array_of_odd_length:  \n");
  int arr[] = {1, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 634};
  size_t length = sizeof(arr) / sizeof(arr[0]);
  int idx = 9, elem = 144;
  printf("%d == %d: %s\n", arr[idx], *binary_search(elem, arr, length),
         parse_bool(&arr[idx] == binary_search(elem, arr, length)));
}

void test_a_value_smaller_than_the_arrays_smallest_value_is_not_found(void) {
  printf("test_a_value_smaller_than_the_arrays_smallest_value_is_not_found:\n");
  int arr[] = {1, 3, 4, 6, 8, 9, 11};

  size_t length = sizeof(arr) / sizeof(arr[0]);

  int elem = 0;
  printf("NULL == %s: %s\n",
         binary_search(elem, arr, length) == NULL ? "NULL" : "",
         parse_bool(NULL == binary_search(elem, arr, length)));
}

void test_finds_a_value_at_the_beginning_of_an_array(void) {
  printf("test_finds_a_value_at_the_beginning_of_an_array:\n");
  int arr[] = {1, 3, 4, 6, 8, 9, 11};

  size_t length = sizeof(arr) / sizeof(arr[0]);

  int idx = 0, elem = 1;
  printf("%d == %d: %s\n", arr[idx], *binary_search(elem, arr, length),
         parse_bool(&arr[idx] == binary_search(elem, arr, length)));
}

void test_finds_a_value_at_the_end_of_an_array(void) {
  printf("test_finds_a_value_at_the_end_of_an_array: \n");
  int arr[] = {1, 3, 4, 6, 8, 9, 11};

  size_t length = sizeof(arr) / sizeof(arr[0]);
  int idx = 6, elem = 11;
  printf("%d == %d: %s\n", arr[idx], *binary_search(elem, arr, length),
         parse_bool(&arr[idx] == binary_search(elem, arr, length)));
}

void test_finds_a_value_in_an_array_of_even_length(void) {
  printf("test_finds_a_value_in_an_array_of_even_length\n");
  int arr[] = {1, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377};

  size_t length = sizeof(arr) / sizeof(arr[0]);

  int idx = 5, elem = 21;
  printf("%d == %d: %s\n", arr[idx], *binary_search(elem, arr, length),
         parse_bool(&arr[idx] == binary_search(elem, arr, length)));
}

void test_identifies_that_a_value_is_not_included_in_the_array(void) {
  printf("test_identifies_that_a_value_is_not_included_in_the_array\n");
  int arr[] = {1, 3, 4, 6, 8, 9, 11};

  size_t length = sizeof(arr) / sizeof(arr[0]);

  int elem = 7;
  printf("NULL == %s: %s\n",
         binary_search(elem, arr, length) == NULL ? "NULL" : "",
         parse_bool(NULL == binary_search(elem, arr, length)));
}

int main(int argc, char *argv[]) {
  int arr[] = {6};
  size_t length = sizeof(arr) / sizeof(arr[0]);
  printf("%d == %d: %s\n", arr[0], *binary_search(6, arr, length),
         parse_bool(&arr[0] == binary_search(6, arr, length)));
  test_a_value_in_the_middle_of_an_array();
  test_finds_a_value_in_an_array_of_odd_length();
  test_a_value_smaller_than_the_arrays_smallest_value_is_not_found();
  test_finds_a_value_at_the_beginning_of_an_array();
  test_finds_a_value_at_the_end_of_an_array();
  test_finds_a_value_in_an_array_of_even_length();
  test_identifies_that_a_value_is_not_included_in_the_array();
  return EXIT_SUCCESS;
}
