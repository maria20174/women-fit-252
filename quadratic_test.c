#include "quadratic.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int main (){
    double r[2];
    assert(solve(0,1,1,r)==-1);
    assert(solve(1,0,-1,r)==2);
    assert(fabs(r[0]-(-1.0))<1e-9);
    assert(fabs(r[1]-(1.0))<1e-9);
    assert(solve(1,0,0,r)==1);
    assert(fabs(r[0])<1e-9);
    assert(solve(1,0,1,r)==0);
    assert(solve(1,-1e10,-1,r)==2);
    assert(fabs(r[0]-(-1e-10))<5e-11);
    assert(fabs(r[1]-1e-10)<1.0);
    assert(solve(1,0,-1e-7,r)==2);
    assert(fabs(r[0]-(-3e-4))<5e-5);
    assert(fabs(r[1]-3e-4)<5e-5);
    assert(solve(1,0,-1e-8,r)==1);
    assert(fabs(r[0])<5e-8);
    printf("quadratic: all tested passed");
    return 0;                                
}