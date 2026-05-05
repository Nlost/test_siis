#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double f_exemplu(double x)
{
    return x*x - 5*x +3;
}


double radacina_bisectie(double (*f)(double), double a, double b, double eps)
{
    double fa = f(a);
    double fb = f(b);

    if (fa == 0.0) {
        return a;
    }
    if (fb == 0.0) {
        return b;
    }
    if (fa * fb > 0.0) {
        fprintf(stderr, "f(a) şi f(b) au acelaşi semn — bisecţia nu se aplică.\n");
        exit(EXIT_FAILURE);
    }

    while (b - a >= eps) {
        double m  = 0.5 * (a + b);
        double fm = f(m);

        if (fm == 0.0) {
            return m;
        }
        if (fa * fm < 0.0) {
            b = m;
        } else {
            a   = m;
            fa = fm;
        }
    }

    return 0.5 * (a + b);
}

static double bisect_rec(double (*ff)(double), double a, double b, double fa,
                         double eps)
{
    if (fa == 0.0) {
        return a;
    }
    if (b - a < eps) {
        return 0.5 * (a + b);
    }

    double m  = 0.5 * (a + b);
    double fm = ff(m);

    if (fm == 0.0) {
        return m;
    }
    if (fa * fm < 0.0) {
        return bisect_rec(ff, a, m, fa, eps);
    }
    return bisect_rec(ff, m, b, fm, eps);
}

double radacina_bisectie_rec(double (*f)(double), double a, double b, double eps)
{
    double fa = f(a);
    double fb = f(b);

    if (fa == 0.0) {
        return a;
    }
    if (fb == 0.0) {
        return b;
    }
    if (fa * fb > 0.0) {
        fprintf(stderr, "f(a) şi f(b) au acelaşi semn — bisecţia nu se aplică.\n");
        exit(EXIT_FAILURE);
    }

    return bisect_rec(f, a, b, fa, eps);
}

int main(void)
{
    /* Caz concret: interval şi precizie */
    const double a_fixed = 0.0;
    const double b_fixed = 3.0;
    double eps;

    printf("Funcţie: f(x) = x^3 + x - 1 pe [%.1f, %.1f]\n", a_fixed, b_fixed);
    printf("f(0) = %.3f, f(1) = %.3f (semne opuse)\n\n", f_exemplu(a_fixed),
           f_exemplu(b_fixed));

    printf("Introduceti precizia dorita (lungime maxima a intervalului, ex: 1e-10): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0.0) {
        fprintf(stderr, "Precizie invalidă.\n");
        return 1;
    }

    double root_it = radacina_bisectie(f_exemplu, a_fixed, b_fixed, eps);
    double root_re = radacina_bisectie_rec(f_exemplu, a_fixed, b_fixed, eps);

    printf("--- iterativ  ---\n");
    printf("Rădăcină aproximată       = %.15f\n", root_it);
    printf("f(rădăcină)               = %.3e\n", f_exemplu(root_it));

    printf("--- recursiv ---\n");
    printf("Rădăcină aproximată       = %.15f\n", root_re);
    printf("f(rădăcină)               = %.3e\n", f_exemplu(root_re));
    printf("Lungime interval final    < %.3e\n", eps);

    return 0;
}
