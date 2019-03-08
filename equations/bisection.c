/*
 * find the root of the equation f(x) = 0
 * use bisection method
 * trivial implementation
 * pros: always converges
 * cons: slow & cannot find multiple or complex roots
 */
#include <stdio.h>
#include <math.h>

typedef double (*function)(double);

int sgn(double x)
{
    return (x > 0) - (x < 0);
}

double poo(double x) // f should be continuous on the interval [a, b]
{
    return sin(x);
}

double bisect(function f, double a, double b, double threshold, int iterations)
{
    double p;
    for (int i = 0; i < iterations; ++i)
    {
        p = a + (b - a) / 2; // compute p_i, avoid upper overflow, lower overflow is tolerable
        if (!f(p) || b - a < threshold)
            return p;
        if (sgn(f(a)) * sgn(f(p)) > 0) // use sgn to save time
            a = p;
        else
            b = p;
    }
    return p;
}

int main()
{
    printf("%f", bisect(poo, 1, 6, 0.000001, 10000000)); // should be pi
    return 0;
}