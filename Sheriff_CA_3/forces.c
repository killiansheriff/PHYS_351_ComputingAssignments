/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 20-Feb-2020
 */

// forces.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "forces.h"

// forces and velocities
// This is problem-specific
// For our problem (Euler Equation), implement the right hand side of
// dq_1/dt = ( (I_2 - I_3)/I_1 ) q_2 q_3
// dq_2/dt = ( (I_3 - I_1)/I_2 ) q_3 q_1
// dq_3/dt = ( (I_1 - I_2)/I_3 ) q_1 q_2
// Take q[0] to be q_3 and I_prin[0] to be I_3

double QVelo0(double *q, double t, int num_elems)
{
        double f;

        double I1 = PARAM_DATA.I_prin[1]; //get I parameters
        double I2 = PARAM_DATA.I_prin[2];
        double I3 = PARAM_DATA.I_prin[0];
        double q_1 = *(q+1);//get the correct value of q
        double q_2 = *(q+2);

        f = ((I1-I2)/I3)*q_1*q_2;

        return f;
}// QVelo0

double QVelo1(double *q, double t, int num_elems)
{
        double f;

        double I1 = PARAM_DATA.I_prin[1]; //get I parameters
        double I2 = PARAM_DATA.I_prin[2];
        double I3 = PARAM_DATA.I_prin[0];
        double q_2 = *(q+2);//get the correct value of q
        double q_3 = *q;

        f = ((I2-I3)/I1)*q_2*q_3; //calculate force
        return f;
}// QVelo1

double QVelo2(double *q, double t, int num_elems)
{
        double f;

        double I1 = PARAM_DATA.I_prin[1]; //get I parameters
        double I2 = PARAM_DATA.I_prin[2];
        double I3 = PARAM_DATA.I_prin[0];
        double q_1 = *(q+1); //get the correct value of q
        double q_3 = *q;

        f = ((I3-I1)/I2)*q_3*q_1; //calculate force

        return f;
}// QVelo2
