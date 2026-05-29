#include "integr.h"
#include <math.h>

double integral(double (*f)(double), double a, double b, unsigned int n) {
  if (n == 0)
    return 0.0;

  double h = (b - a) / n;
  double sum = 0.5 * (f(a) + f(b));

  for (unsigned int i = 1; i < n; i++) {
    sum += f(a + i * h);
  }

  return sum * h;
}
