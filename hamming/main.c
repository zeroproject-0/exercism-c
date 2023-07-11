#include <stdio.h>
#include <string.h>

int compute(const char *lhs, const char *rhs) {
  size_t size = strlen(lhs);
  if (size != strlen(rhs))
    return -1;

  int res = 0;
  for (int i = 0; i < (int)size; ++i) {
    if (lhs[i] != rhs[i])
      res++;
  }

  return res;
}

int main(int argc, char *argv[]) {
  char *text1 = "GGACGGATTCTG";
  char *text2 = "AGGACGGATTCT";

  printf("%s & %s: %d\n", text1, text2, compute(text1, text2));

  return 0;
}
