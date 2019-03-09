/*
 * fixed-point iteration
 * find root of f(x) = 0 is equivalent to find the fixed-point of g(x), where g(x) = f(x) + x
 * there could be many equivalent equations, i chose the simplest one
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*function)(double);

double poo(double x)
{
    return cos(x);
}

double fixedpoint(function f, double p0, double threshold, int iterations)
{
    double p;
    for (int i = 0; i < iterations; ++i)
    {
        p = f(p0) + p0; // p = g(p0)
        // printf("%f\n", p);
        if (fabs(p - p0) < threshold)
            return p;
        p0 = p;
    }
    return p;
}

int main()
{
    printf("%f", fixedpoint(poo, 3, 0.000001, 1000000)); // should be pi/2
    return 0;
}