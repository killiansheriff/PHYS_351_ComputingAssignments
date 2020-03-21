
#ifndef EVOLVE_H
#define EVOLVE_H
#include "params.h"

void EvolveNeq(double *q);
void RecordAStep(FILE *output, double t_now, double *q, int num_eq);
double GetAngle(double q);

#endif
