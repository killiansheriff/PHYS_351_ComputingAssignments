/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   05-Mar-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 05-Mar-2020
 */

#ifndef PARAMS_H
#define PARAMS_H
// this makes sure the header is only included once
#define PI 3.1415926535897932385 // numerical value of pi

typedef double (*FuncPt)(double *q, double t, int num_elems); // a vector of functions

typedef struct euler_params {
        double *q_i; // intial value for the dynamic variables
        double t_i; // inital time
        double t_f; // final time
        FuncPt *QVelos; //array of functions
        double h; // the time step size
        int num_eq; // number of first order ODEs
        double prec_goal; // precision of claculations
        double mass1;
        double mass2;// the masses in the double pendulam
        double length1;
        double length2;// the length of the rods in the pendulam
} EulerParams;

EulerParams PARAM_DATA;


#endif
