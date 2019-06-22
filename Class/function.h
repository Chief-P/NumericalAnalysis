#pragma once
#include <iostream>
#include <vector>

namespace NumericalAnalysis
{
    // single-variable function
    class Function
    {
    public:
        typedef double (*fp)(const double x); // function pointer
        typedef unsigned int uint;

        virtual ~Function();

        virtual Function operator+(const Function &g);
        virtual Function operator*(const Function &g);
        virtual Function operator-();
        virtual Function operator[](double x);
    };

    class ContinuousFunction : public Function
    {
    public:
        ContinuousFunction(const fp g) : f(g) {};
        virtual ~ContinuousFunction();

        virtual double derivative(const double x, const double h = 0.01);
        virtual double integral(const double a, const double b);

        virtual Function operator+(const Function &g);
        virtual Function operator*(const Function &g);
        virtual Function operator-();
        virtual Function operator[](double x);

    private:
        fp f;
    };

    class Polynomial : public ContinuousFunction
    {
    public:
        Polynomial();
        Polynomial(const std::vector<double> &coef); // direct initialization
        Polynomial(const std::vector<double> &x, const std::vector<double> &y); // interpolation
        Polynomial(const std::vector<double> &x, const ContinuousFunction &cf);
        Polynomial(const DiscreteFunction &df);
        ~Polynomial();

        double derivative(const double x, const double h = 0.01);
        double integral(const double a, const double b);

        Function operator+(const Function &g);
        Function operator*(const Function &g);
        Function operator-();
        Function operator[](double x);

    private:
        void interpolate(const std::vector<double> &x, const std::vector<double> &y);

        std::vector<double> coef;
        uint order;
    };

    class DiscreteFunction : public Function
    {
    public:
        DiscreteFunction(const std::vector<double> &val);
        ~DiscreteFunction();

        Function operator+(const Function &g);
        Function operator*(const Function &g);
        Function operator-();
        Function operator[](double x);

    private:
        std::vector<double> val;
    };
}