/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   25-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 25-Jan-2020
 */

// This file is evolve.h
#ifndef EVOLVE_H
#define EVOLVE_H
// *** Assignment 2 Tasks ****
void Evolve(double *x, double *p);
void AdvanceOneStep(double *x, double *p, int it_now, int choice);
// This is the workhorse
// It advances x_now and p_now by time step h to x_next and p_next
// using x_in and p_in on the right hand side
void OneStep
(double x_now, double p_now, double x_in, double p_in,
double *x_next, double *p_next, double h);
void ForwardEulerStep
(double x_now, double p_now, double *x_next, double *p_next, double h);
void BackwardEulerStep
(double x_now, double p_now, double *x_next, double *p_next, double h);
void Leapfrog1Step
(double x_now, double p_now, double *x_next, double *p_next, double h);
void Leapfrog2Step
(double x_now, double p_now, double *x_next, double *p_next, double h);

// We will get to the following later
// void VelocityVerletStep
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// void PositionVerletStep
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// void HeunStep
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// void Heun3Step
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// void RK4Step
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// void RuthForestStep
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// void PEFRLStep
// (double x_now, double p_now, double *x_next, double *p_next, double h);
// int OneStepWithErr
// (double x_now, double p_now, double *x_next, double *p_next,
// double *h_next, double h);
// void AdaptiveVerletStep
// (double x_now, double p_now, double *x_next, double *p_next, double h);
#endif
