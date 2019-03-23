/*
 * Doolittle Method for LU fractorization
 * solve the linear system Ax = b, where A is of size n by n
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
 * A: of size n by n
 * b: of size n by 1
 * b: the solution
 */
void doolittle(double *A, double *b, int n)
{
    for (int i = 0; i < n; ++i) // compact form of LU
    {
        for (int j = i; j < n; ++j)
            for (int k = 0; k < i; ++k)
                A[i * n + j] -= A[i * n + k] * A[k * n + j];
        for (int j = i + 1; j < n; ++j)
        {
            for (int k = 0; k < i; ++k)
                A[j * n + i] -= A[j * n + k] * A[k * n + i];
            A[j * n + i] /= A[i * n + i];
        }
    }
    for (int j = 0; j < n - 1; ++j) // solve Ly = b, forward substitution
        for (int i = j + 1; i < n; ++i)
            b[i] -= A[i * n + j] * b[j];
    for (int j = n - 1; j > 0; --j) // solv Ux = y, backward substitution
        for (int i = j - 1; i >= 0; --i)
            b[i] -= A[i * n + j] / A[j * n + j] * b[j];
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

    double *A = malloc(sizeof(double) * n * n);
    double *b = malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fscanf(fp, "%lf", &A[i * n + j]);
    for (int i = 0; i < n; ++i)
        fscanf(fp, "%lf", &b[i]);
    fclose(fp);

    doolittle(A, b, n);

    for (int i = 0; i < n + 1 - 1; ++i)
        printf("%f\n", b[i]);

    free(A);
    free(b);

    return 0;
}