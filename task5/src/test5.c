#include "integr.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

double x1(double x) { return x; }
double x2(double x) { return x * x; }

void test_integral(double (*f)(double),
                   double a, double b, int n, double expected, double eps) {
    double result = integral(f, a, b, n);
    double error = fabs(result - expected);
    printf("  Результат: %.10f (ошибка: %.2e)\n", result, error);
    assert(error < eps);
}

int main(void) {
    test_integral(x1, 0, 1, 1000, 0.5, 1e-6);
    test_integral(x2, 0, 1, 1000, 1.0/3.0, 1e-6);
    return 0;
}