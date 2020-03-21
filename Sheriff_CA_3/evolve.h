/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 20-Feb-2020
 */

#ifndef EVOLVE_H
#define EVOLVE_H
#include "params.h"

//calls evolveNeq OneStepNeq RK4Step

void EvolveNeq(double *q);

void OneStepNeq(double *q_now, double *q_in, double *q_next, FuncPt *QVelos, double t_in, double h, int num_eq);

void RK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, double h, int num_eq);
#endif
