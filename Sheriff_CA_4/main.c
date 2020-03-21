/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   05-Mar-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 05-Mar-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "params.h"
#include "init.h"
#include "evolve.h"

// The goal of this assignment is to solve the double pendulum problem // numerically.
// The dynamical variables are theta_1, theta_2, p_1, and p_2
// They correspond to q[0], q[1], q[2], and q[3], respectively.
int main(int argc, char **argv)
{
        char *input_file; // Input file name double *q;
        double t_i, t_f;
        double *q;
        input_file = argv[1];
        ReadInParams(input_file); PrintParams();
// allocate memory space to q
        q = vector_malloc(PARAM_DATA.num_eq);
        InitializeNeq(q);
        EvolveNeq(q); // evolve q
        return 0;
}// main
