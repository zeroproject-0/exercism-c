#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse(const char *value) {
  int len = (int)strlen(value);
  char *new_str = calloc(len + 1, sizeof(char));

  for (int i = len; i > 0; --i)
    new_str[len - i] = value[i - 1];

  return new_str;
}

void test_reverse(char *phrase, char *expected) {
  char *actual = reverse(phrase);
  printf("%s\n", expected == actual ? "TRUE" : "FALSE");
  free(actual);
}

static void test_an_empty_string(void) { test_reverse("", ""); }
static void test_a_word(void) { test_reverse("robot", "tobor"); }
static void test_a_capitalized_word(void) { test_reverse("Ramen", "nemaR"); }
static void test_a_sentence_with_punctuation(void) {
  test_reverse("I'm hungry!", "!yrgnuh m'I");
}
static void test_a_palindrome(void) { test_reverse("racecar", "racecar"); }

static void test_an_even_sized_word(void) { test_reverse("drawer", "reward"); }

int main(int argc, char *argv[]) {
  printf("Reverse String\n");
  test_an_empty_string();
  test_a_word();
  test_a_capitalized_word();
  test_a_sentence_with_punctuation();
  test_a_palindrome();
  test_an_even_sized_word();
  return EXIT_SUCCESS;
}
