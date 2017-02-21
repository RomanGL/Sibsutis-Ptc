#include <stdio.h>
#include <math.h>

double func(double x)
{
    return exp(-x * x);
}

int main(int argc, char **argv)
{
    const double a = -4.0;
    const double b = 4.0;
    const int n = 100;

    double h = (b - a) / n;
    double s = 0.0;

    for (int i = 0; i < n; i++)
        s += func(a + h * (i + 0.5));

    s *= h;

    printf("Result Pi: %.12f\n", s * s);
    return 0;
}