/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 20-Feb-2020
 */

#ifndef PARAM_H
#define PARAM_H

typedef double (*FuncPt)(double *q, double t, int num_elems); //defines function type

typedef struct neq_params
{
        int num_eq; // number of equations - the same as the number of dynamic variables

        double *q_i; // initial values for the dynamic variables
        double t_i; // initial time
        double t_f; // final time
        int it_max; // the number of time steps
        double h; // the time step size

        FuncPt *QVelos;

        //problem specific input
        double *I_prin; //principal moments of inertia

} NeqParams;
NeqParams PARAM_DATA; //so can be shared globally with params.h
#endif
