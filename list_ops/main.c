#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int list_element_t;

typedef struct {
  size_t length;
  list_element_t *elements;
} list_t;

void print_list(list_t *l) {
  printf("Actual: NULL == %s\n", l ? "NOT NULL" : "NULL");
  if (l == NULL)
    return;

  printf("Length: %zu\n", l->length);
  for (size_t i = 0; i < l->length; i++) {
    printf("%zu) %d\n", i, l->elements[i]);
  }
}

list_t *new_list(size_t length, list_element_t elements[]) {
  /* printf("length: %zu\n", length); */
  /* printf("%zu \n", sizeof(list_t) + (length * sizeof(list_element_t))); */
  list_t *l = malloc(sizeof(list_t));

  l->length = length;
  l->elements = calloc(length, sizeof(list_element_t));

  if (elements != NULL) {
    for (size_t i = 0; i < length; i++) {
      l->elements[i] = elements[i];
    }
  }
  /* print_list(l); */

  return l;
}

// append entries to a list and return the new list
list_t *append_list(list_t *list1, list_t *list2) {
  /* printf("hasjehlkjahse\n"); */
  list_t *l = new_list(list1->length + list2->length, list1->elements);

  for (size_t i = 0; i < list2->length; i++) {
    l->elements[i + list1->length] = list2->elements[i];
  }

  return l;
}

// filter list returning only values that satisfy the filter function
list_t *filter_list(list_t *list, bool (*filter)(list_element_t)) {
  list_t *l = new_list(list->length, list->elements);
  size_t new_size = 0;
  for (size_t i = 0; i < list->length; ++i) {
    if (filter(list->elements[i])) {
      l->elements[new_size++] = list->elements[i];
    }
  }

  return new_list(new_size, l->elements);
}

// returns the length of the list
size_t length_list(list_t *list) { return list->length; }

// return a list of elements whose values equal the list value transformed by
// the mapping function
list_t *map_list(list_t *list, list_element_t (*map)(list_element_t)) {
  list_t *l = new_list(list->length, list->elements);

  for (size_t i = 0; i < list->length; ++i)
    l->elements[i] = map(list->elements[i]);

  return l;
}

// folds (reduces) the given list from the left with a function
list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t)) {
  for (size_t i = 0; i < list->length; ++i) {
    initial = foldl(list->elements[i], initial);
  }

  return initial;
}

// folds (reduces) the given list from the right with a function
list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t)) {
  if (list->length == 0)
    return initial;

  for (int i = (int)list->length - 1; i >= 0; --i) {
    initial = foldr(list->elements[i], initial);
  }

  return initial;
}

// reverse the elements of the list
list_t *reverse_list(list_t *list) {
  list_t *l = new_list(list->length, NULL);

  for (int i = (int)list->length; i >= 0; --i) {
    l->elements[list->length - i] = list->elements[i - 1];
  }

  return l;
}

// destroy the entire list
// list will be a dangling pointer after calling this method on it
void delete_list(list_t *list) { free(list); }

static bool filter_modulo(list_element_t element)

{

  return (element % 2 == 1);
}

static list_element_t map_increment(list_element_t element)

{

  return element + 1;
}

static list_element_t fold_multiply(list_element_t element,

                                    list_element_t accumulator)

{

  return element * accumulator;
}

static list_element_t fold_add(list_element_t element,

                               list_element_t accumulator)

{

  return element + accumulator;
}

static list_element_t fold_divide(list_element_t element,

                                  list_element_t accumulator)

{

  return (accumulator == 0) ? 0 : element / accumulator;
}

static void call_delete_list(list_t **list) {
  delete_list(*list);
  *list = NULL;
}

void check_lists_match(size_t expected_length,
                       list_element_t expected_elements[], list_t *actual) {
  printf("Actual: NULL == %s\n", actual ? "NOT NULL" : "NULL");
  if (actual == NULL)
    return;
  printf("Length: %zu == %zu\n", expected_length, actual->length);
  if (expected_length != actual->length)
    return;

  for (size_t i = 0; i < actual->length; i++) {
    printf("%zu) %d == %d\n", i, expected_elements[i], actual->elements[i]);
  }
}

static list_t *list = NULL;
static list_t *list2 = NULL;
static list_t *actual = NULL;

void test_append_empty_lists(void) {
  printf("\ntest_append_empty_lists\n");

  list = new_list(0, NULL);
  list2 = new_list(0, NULL);
  actual = append_list(list, list2);
  check_lists_match(0, NULL, actual);
  call_delete_list(&list);
  call_delete_list(&list2);
  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_append_list_to_empty_list(void) {
  printf("\ntest_append_list_to_empty_list\n");
  list = new_list(0, NULL);
  list2 = new_list(3, (list_element_t[]){1, 3, 4});
  size_t expected_length = 3;
  list_element_t expected_elements[] = {1, 3, 4};
  actual = append_list(list, list2);
  check_lists_match(expected_length, expected_elements, actual);
  call_delete_list(&list);
  call_delete_list(&list2);
  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_append_empty_list_to_list(void) {
  printf("\ntest_append_empty_list_to_list\n");
  list = new_list(4, (list_element_t[]){1, 2, 3, 4});
  list2 = new_list(0, NULL);
  size_t expected_length = 4;
  list_element_t expected_elements[] = {1, 2, 3, 4};
  actual = append_list(list, list2);
  check_lists_match(expected_length, expected_elements, actual);
  call_delete_list(&list);
  call_delete_list(&list2);
  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_append_non_empty_lists(void) {
  printf("\ntest_append_non_empty_list\n");
  list = new_list(2, (list_element_t[]){1, 2});
  list2 = new_list(4, (list_element_t[]){2, 3, 4, 5});
  size_t expected_length = 6;
  list_element_t expected_elements[] = {1, 2, 2, 3, 4, 5};
  actual = append_list(list, list2);
  check_lists_match(expected_length, expected_elements, actual);
  call_delete_list(&list);
  call_delete_list(&list2);
  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_filter_empty_list(void) {
  printf("\ntest_filter_empty_list\n");
  list = new_list(0, NULL);
  actual = filter_list(list, filter_modulo);
  check_lists_match(0, NULL, actual);
  call_delete_list(&list);
  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_filter_non_empty_list(void) {
  printf("\ntest_filter_non_empty_list\n");
  list = new_list(5, (list_element_t[]){1, 2, 3, 4, 5});

  size_t expected_length = 3;

  list_element_t expected_elements[] = {1, 3, 5};

  actual = filter_list(list, filter_modulo);

  check_lists_match(expected_length, expected_elements, actual);

  call_delete_list(&list);

  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_length_empty_list(void) {
  printf("\ntest_length_empty_list\n");
  list = new_list(0, NULL);

  size_t expected = 0;

  size_t actual = length_list(list);

  printf("%zu == %zu\n", expected, actual);
  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_length_non_empty_list(void) {
  printf("\ntest_length_non_empty_list\n");
  list = new_list(4, (list_element_t[]){1, 2, 3, 4});

  size_t expected = 4;

  size_t actual = length_list(list);
  printf("%zu == %zu\n", expected, actual);
  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_map_empty_list(void) {
  printf("\ntest_map_empty_list\n");
  list = new_list(0, NULL);

  actual = map_list(list, map_increment);

  check_lists_match(0, NULL, actual);
  call_delete_list(&list);
  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_map_non_empty_list(void) {
  printf("\ntest_map_non_empty_list\n");

  list = new_list(4, (list_element_t[]){1, 3, 5, 7});

  size_t expected_length = 4;

  list_element_t expected_elements[] = {2, 4, 6, 8};

  actual = map_list(list, map_increment);

  check_lists_match(expected_length, expected_elements, actual);

  call_delete_list(&list);

  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

void test_foldl_empty_list(void) {
  printf("\ntest_foldl_empty_list\n");
  list = new_list(0, NULL);

  list_element_t initial = 2;

  list_element_t expected = 2;

  list_element_t actual = foldl_list(list, initial, fold_divide);

  printf("%d == %d\n", expected, actual);

  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_foldl_direction_independent_function_applied_to_non_empty_list(void) {
  printf("\ntest_foldl_direction_independent_function_applied_to_non_empty_"
         "list\n");
  list = new_list(4, (list_element_t[]){1, 2, 3, 4});

  list_element_t initial = 5;

  list_element_t expected = 15;

  list_element_t actual = foldl_list(list, initial, fold_add);

  printf("%d == %d\n", expected, actual);

  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_foldl_direction_dependent_function_applied_to_non_empty_list(void) {
  printf(
      "\ntest_foldl_direction_dependent_function_applied_to_non_empty_list\n");
  list = new_list(2, (list_element_t[]){2, 5});

  list_element_t initial = 5;

  list_element_t expected = 0;

  list_element_t actual = foldl_list(list, initial, fold_divide);

  printf("%d == %d\n", expected, actual);

  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_foldr_empty_list(void) {
  printf("\ntest_foldr_empty_list\n");
  list = new_list(0, NULL);

  list_element_t initial = 2;

  list_element_t expected = 2;

  list_element_t actual = foldr_list(list, initial, fold_multiply);

  printf("%d == %d\n", expected, actual);

  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_foldr_direction_independent_function_applied_to_non_empty_list(void) {
  printf("\ntest_foldr_direction_independent_function_applied_to_non_empty_"
         "list\n");
  list = new_list(4, (list_element_t[]){1, 2, 3, 4});
  list_element_t initial = 5;
  list_element_t expected = 15;
  list_element_t actual = foldr_list(list, initial, fold_add);
  printf("%d == %d\n", expected, actual);
  call_delete_list(&list);
  printf("-----------------------------------\n");
}

void test_reverse_non_empty_list(void) {
  printf("\ntest_reverse_non_empty_list\n");
  list = new_list(4, (list_element_t[]){1, 3, 5, 7});

  size_t expected_length = 4;

  list_element_t expected_elements[] = {7, 5, 3, 1};

  actual = reverse_list(list);

  check_lists_match(expected_length, expected_elements, actual);

  call_delete_list(&list);

  call_delete_list(&actual);
  printf("-----------------------------------\n");
}

int main(int argc, char *argv[]) {
  printf("List Ops\n");
  test_append_empty_lists();
  test_append_list_to_empty_list();
  test_append_empty_list_to_list();
  test_append_non_empty_lists();
  test_filter_empty_list();
  test_filter_non_empty_list();
  test_length_empty_list();
  test_length_non_empty_list();
  test_map_empty_list();
  test_map_non_empty_list();
  test_foldl_empty_list();
  test_foldl_direction_independent_function_applied_to_non_empty_list();
  test_foldl_direction_dependent_function_applied_to_non_empty_list();
  test_foldr_empty_list();
  test_foldr_direction_independent_function_applied_to_non_empty_list();
  test_reverse_non_empty_list();

  return EXIT_SUCCESS;
}
