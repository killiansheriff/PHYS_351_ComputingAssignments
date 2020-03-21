/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   05-Mar-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 05-Mar-2020
 */

#ifndef FORCES_H
#define FORCES_H
#include "params.h"

void Translate
        (double *q, double *theta_1, double *theta_2, double *p_1, double *p_2,
        double *mass1, double *mass2, double *length1, double *length2);

double QVelo0(double *q, double t, int num_elems);
double QVelo1(double *q, double t, int num_elems);
double QVelo2(double *q, double t, int num_elems);
double QVelo3(double *q, double t, int num_elems);

double TotalEnergy(double *q);




#endif
