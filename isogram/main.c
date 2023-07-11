#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char char_to_lower(char a) {
  return (int)a > 64 && (int)a < 91 ? (char)((int)a + 32) : a;
}

bool is_isogram(const char phrase[]) {
  if (phrase == NULL)
    return false;

  int size = strlen(phrase);

  for (int i = 0; i < size; ++i) {
    char a = char_to_lower(phrase[i]);

    if (a == ' ' || a == '-')
      continue;

    for (int j = 0; j < size; ++j) {
      char b = char_to_lower(phrase[j]);

      if (i != j && (b != ' ' || b != '-')) {
        if (a == b)
          return false;
      }
    }
  }

  return true;
}

int main(int argc, char *argv[]) {
  char *texts[] = {"",
                   NULL,
                   "isogram",
                   "eleven",
                   "zzyzx",
                   "subdermatoglyphic",
                   "Alphabet",
                   "alphAbet",
                   "thumbscrew-japingly",
                   "thumbscrew-jappingly",
                   "six-year-old",
                   "Emily Jung Schwartzkopf",
                   "accentor",
                   "angola",
                   "up-to-date"};

  for (int i = 0; i < 15; ++i) {
    printf("%s: %s\n", texts[i], is_isogram(texts[i]) ? "True" : "False");
  }

  return 0;
}
