/*
 * Newton-Raphson method
 * linearize a nonlinear function using Taylor's expansion
 * convergence depends on the initial value
 */
#include <stdio.h>
#include <math.h>

typedef double (*function)(double x);

double poo(double x)
{
    return sin(x);
}

double derivative(function f, double x)
{
    double delta = 0.000001;
    return (f(x + delta) - f(x)) / delta;
}

double newton(function f, double p0, double threshold, int iterations)
{
    double p;
    for (int i = 0; i < iterations; ++i)
    {
        p = p0 - f(p0) / derivative(f, p0);
        if (fabs(f(p)) < threshold)
            return p;
        p0 = p;
    }
    return p;
}

int main()
{
    printf("%f", newton(poo, 2, 0.000001, 1000000)); // should be pi
    return 0;
}