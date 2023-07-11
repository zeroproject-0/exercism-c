#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float numerator;
  float denominator;
} rational_t;

rational_t reduce(rational_t r);

rational_t add(rational_t n1, rational_t n2);

rational_t subtract(rational_t n1, rational_t n2);

rational_t multiply(rational_t n1, rational_t n2);

rational_t divide(rational_t n1, rational_t n2);

float absf(float n);

rational_t absolute(rational_t n);

rational_t exp_rational(rational_t n, int16_t e);

float exp_real(uint16_t b, rational_t e);

// ----------------------------- IMPl

void r_print(char *m, rational_t r) {
  printf("%s: %f / %f\n", m, r.numerator, r.denominator);
}

float absf(float n) { return n < 0 ? n * -1 : n; }

rational_t reduce(rational_t r) {
  rational_t n = {r.numerator, r.denominator};
  if (n.numerator == 0)
    n.denominator = 1;
  if (r.denominator < 0) {
    n.numerator *= -1;
    n.denominator = absf(r.denominator);
  }

  float min =
      absf(n.numerator) < n.denominator ? absf(n.numerator) : n.denominator;

  for (int i = 2; i <= min; ++i) {
    while ((int)absf(n.denominator) % i == 0 &&
           (int)absf(n.numerator) % i == 0) {
      n.numerator /= i;
      n.denominator /= i;
    }
  }

  return n;
}

rational_t add(rational_t n1, rational_t n2) {
  rational_t r = {0, 0};

  r.numerator =
      (n1.numerator * n2.denominator) + (n1.denominator * n2.numerator);
  r.denominator = (n1.denominator * n2.denominator);

  return reduce(r);
}

rational_t subtract(rational_t n1, rational_t n2) {
  rational_t r = {0, 0};

  r.numerator =
      (n1.numerator * n2.denominator) - (n1.denominator * n2.numerator);
  r.denominator = (n1.denominator * n2.denominator);

  return reduce(r);
}

rational_t multiply(rational_t n1, rational_t n2) {
  rational_t r = {0, 0};

  r.numerator = n1.numerator * n2.numerator;
  r.denominator = n1.denominator * n2.denominator;

  return reduce(r);
}

rational_t divide(rational_t n1, rational_t n2) {
  rational_t r = {0, 0};

  r.numerator = n1.numerator * n2.denominator;
  r.denominator = n1.denominator * n2.numerator;

  return reduce(r);
}

rational_t absolute(rational_t n) {
  rational_t r = {0, 0};

  r.numerator = absf(n.numerator);
  r.denominator = absf(n.denominator);

  return reduce(r);
}

rational_t exp_rational(rational_t n, int16_t e) {

  float n1 = powf(n.numerator, abs(e));
  float n2 = powf(n.denominator, abs(e));
  rational_t r = e < 0 ? (rational_t){n2, n1} : (rational_t){n1, n2};
  return reduce(r);
}

float exp_real(uint16_t b, rational_t e) {
  return powf(powf(b, e.numerator), 1.0 / e.denominator);
}
