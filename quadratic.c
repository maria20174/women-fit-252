#include "quadratic.h"
#include <math.h>

int solve(double a, double b, double c, double r[2]){
    if (a == 0) return -1;

    double d=b*b - 4*a*c;
    double eps = 1e-10*(b*b+ fabs(4*a*c));
    if (d>eps) {
        double sq = sqrt(d);
        double q;
        if (b>=0)
            q = -0.5*(b+sq);
            else
            q = -0.5*(b-sq);
            r[0] = q/a;
            r[1]=c/q;
            if (r[0]>r[1]){
                double t = r[0];
                r[0] = r[1];
                r[1]=t;
            }
            return 2;

    }

    if (d >= -eps) {
        r[0] = -b/(2*a);
        return 1;
    }
    return 0;
}