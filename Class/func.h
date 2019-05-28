#pragma once
#include <iostream>
#include <vector>

namespace NumericalAnalysis
{
    class Function
    {
    public:
        typedef double (*fp)(const double x); // function pointer
        Function();
        virtual ~Function();
        virtual double derivative(const double x, const double h = 0.01);
        virtual double integral(const double a, const double b);
        Function operator+(Function g);
        Function operator*(Function g);
        Function operator-();
    };

    class ContinuousFunction : Function
    {
    public:
        ContinuousFunction(const fp g) : f(g) {};
        ~ContinuousFunction();
    private:
        fp f;
    };

    class DiscreteFunction : Function
    {
    public:
        DiscreteFunction(const std::vector<double> &val);
        ~DiscreteFunction();
    private:
        std::vector<double> f;
    };

    class Polynomial : Function
    {
    public:
        Polynomial();
        Polynomial(const std::vector<double> &coef);
        ~Polynomial();
    private:
        std::vector<double> coef;
    };
}