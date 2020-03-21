/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   25-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 30-Jan-2020
 */

// This file is evolve.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "evolve.h"
#include "forces.h"

void Evolve(double *x, double *p)//runs advanceonestep for each time interval
{
        int it, it_max, choice;

        it_max = PARAM_DATA.it_max;//get values from param
        choice = PARAM_DATA.choice;

        for(it=0; it<it_max; it++)
        {
                AdvanceOneStep(x, p, it, choice);
        }// it-loop

        return;
}// Evolve

// Advances x and p by one step
void AdvanceOneStep(double *x, double *p, int it_now, int choice)//depending on choice runs different evolves
{
        double x_now, p_now, x_next, p_next;
        double v, f, h;

        h = PARAM_DATA.h;

        x_now = x[it_now];//set now to the position and momentum at it_now
        p_now = p[it_now];

        int it_next;
        it_next = it_now +1;

        if(choice == 1) // Forward Euler
        {
                ForwardEulerStep(x_now, p_now, &x_next, &p_next, h);
        }
        else if(choice == 2) // Backward Euler
        {
                BackwardEulerStep(x_now, p_now, &x_next, &p_next, h);
        }
        else if(choice == 3) // Leapfrog 1
        {
                Leapfrog1Step(x_now, p_now, &x_next, &p_next, h);
        }
        else if(choice == 4) // Leapfrog 2
        {
                Leapfrog2Step(x_now, p_now, &x_next, &p_next, h);

        }
        else
        {
                fprintf(stderr, "choice = %d is not yet implemented.\n",choice);
                exit(1);
        }

        x[it_next] = x_next;//set next to be position and momentum at it_next
        p[it_next] = p_next;
        return;
}// AdvanceOneStep


void OneStep(double x_now, double p_now, double x_in, double p_in,double *x_next, double *p_next, double h)
{
        double x, p;

        x = x_now + h*Velocity(p_in);//sets x given an inputed x_now, x_in
        p = p_now + h*Force(x_in);//sets p given an inputed p_now, p_in

        *x_next = x;//sets value at x_next as x
        *p_next = p;//sets value at p_next as p
        return;
}// OneStep


void ForwardEulerStep
        (double x_now, double p_now, double *x_next, double *p_next, double h)
{
        double x, p;
        x = x_now;
        p = p_now;
        OneStep(x_now, p_now, x_now, p_now, x_next, p_next, h);//runs oneStep with x and p in for p_in and x_in

        return;
}// ForwardEulerStep


void BackwardEulerStep
        (double x_now, double p_now, double *x_next, double *p_next, double h)
{
        double x_1, p_1, x_2, p_2;
        double err, TOL;
        int iter, iter_max;


        iter_max=100;//max amount of iterations
        TOL=pow(10,-10);//set

        x_1 = x_now;
        p_1 = p_now;

        for(iter=0; iter < iter_max; iter++)//iterates through onstep with x_1 and p_2 as x_in and p_in
        {
                OneStep(x_now, p_now, x_1, p_1, &x_2, &p_2, h);
                err = fabs(p_2-p_1)+fabs(x_2-x_1);//calculate err
                p_1 = p_2;
                x_1 = x_2;
        }// iter-loop
        if(err >= TOL)

        {

                fprintf(stderr, "Could not converge");
                exit(1);//exits the program
        }
        else
        {
            // This means that the iteration did converge
                *x_next = x_2;
                *p_next = p_2;
        }
        return;
}// BackwardEulerStep

// Leapfrog1
void Leapfrog1Step
        (double x_now, double p_now, double *x_next, double *p_next, double h)
{

        double p_step, x_step;
        p_step = p_now + Force(x_now)*h;//defines p_step
        x_step = x_now + Velocity(p_step)*h;//defines x_step
        *x_next = x_step;//reassigns x_next and p_next
        *p_next = p_step;

        return;
}// Leapfrog1Step

// Leapfrog2
void Leapfrog2Step
        (double x_now, double p_now, double *x_next, double *p_next, double h)
{

        double p_step, x_step;

        x_step = x_now + Velocity(p_now)*h;//defines x_step
        p_step = p_now + Force(x_step)*h;//defines p_step

        *x_next = x_step;//reassigns x_next and p_next
        *p_next = p_step;

        return;
}// Leapfrog2Step
