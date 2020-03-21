/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   25-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 29-Jan-2020
 */
// This file is forces.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "forces.h"
// forces and velocities
// this is simply v = p/m
double Velocity(double p)
{
        double v, mass;

        mass = PARAM_DATA.mass;
        v=p*1.0/mass;

        return v;
}// Velocity

double Force(double x)
{
        double f, k;

        k=PARAM_DATA.k_spring;
        f=-k*1.0*x;

        return f;
}// Force
