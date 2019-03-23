/*
 * Gaussian Elimination (with bugs)
 * directly solve the linear system Ax = b, where A is of size n by n
 * read data from data.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

void swapRow(double *A, int n, int a, int b)
{
    if (a == b)
        return;
    for (int j = 0; j < n; ++j) // in fact, a < b
    {
        double tmp = A[a * n + j];
        A[a * n + j] = A[b * n + j];
        A[b * n + j] = tmp;
    }
}

/* 
 * A: augmented matrix of size n by (n + 1)
 * x: the solution
 */
void gaussian(double *A, int n, double *x)
{
    for (int j = 0; j < n - 1; ++j) // elimination, non-recursive
    {
        for (int i = j; i < n; ++i) // find the first non-zero element in j-th column
            if (fabs(A[i * (n + 1) + j]) > EPSILON)
            {
                swapRow(A, n + 1, j, i);
                break;
            }
        if (fabs(A[j * (n + 1) + j]) < EPSILON) // all zeros
            continue;
        for (int i = j + 1; i < n; ++i)
        {
            double m = A[i * (n + 1) + j] / A[j * (n + 1) + j]; // division
            A[i * (n + 1) + j] = 0.0;
            for (int k = j + 1; k < n + 1; ++k)
                A[i * (n + 1) + k] -= m * A[j * (n + 1) + k];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
            printf("%f ", A[i * (n + 1) + j]);
        printf("\n");
    }
    for (int j = n - 1; j >= 0; --j) // backward-substitution
    {
        if (fabs(A[j * (n + 1) + j]) < EPSILON)
            return;
        A[j * (n + 1) + n] /= A[j * (n + 1) + j];
        A[j * (n + 1) + j] = 1.0;
        for (int i = j - 1; i >= 0; --i)
        {
            A[i * (n + 1) + n] -= A[i * (n + 1) + j] / A[j * (n + 1) + j] * A[j * (n + 1) + n]; // division
            A[i * (n + 1) + n] /= A[i * (n + 1) + i];
            A[i * (n + 1) + j] = 0.0;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
            printf("%f ", A[i * (n + 1) + j]);
        printf("\n");
    }
    for (int i = 0; i < n; ++i)
        x[i] = A[i * (n + 1) + n];
}

int main()
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("File not exist!\n");
        exit(0);
    }

    int n;
    fscanf(fp, "%d", &n);

    double *A = malloc(sizeof(double) * n * (n + 1)); // augmented matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fscanf(fp, "%lf", &A[i * (n + 1) + j]);
    for (int i = 0; i < n; ++i)
        fscanf(fp, "%lf", &A[i * (n + 1) + n]);
    fclose(fp);

    double *x = malloc(sizeof(double) * n); // solution
    gaussian(A, n, x);

    for (int i = 0; i < n + 1 - 1; ++i)
        printf("%f\n", x[i]);

    free(A);
    free(x);

    return 0;
}