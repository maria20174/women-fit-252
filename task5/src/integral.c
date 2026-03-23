#include "integral.h"
#include <math.h>
#include <stddef.h>   

double integral(double (*f)(double), double a, double b, int n) {
    if (f == NULL || n <= 0) return 0.0;
    if (a == b) return 0.0;
    
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    
    return sum * h;
}