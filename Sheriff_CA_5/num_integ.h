#ifndef NUM_INTEG_H
#define NUM_INTEG_H

double NumIntegrate(double *f, double h, int down, int up, int nmax); //calculates sub integral

double NumIntegrateV(double (*func)(double), double x_down, double x_up, int num_intervals); //calculates dx f(x) from x_down to x_up

double AdaptiveIntegrate(double (*func)(double), double down, double h, double *f_prev, double ans_prev, double tol, int *count); //calculates f(x) using adaptive Simpson

double Integrate(double (*integrand)(double), double x_down, double x_up, double tol, int *count, int limit); //wrapper for AdaptiveIntegrate

#endif
