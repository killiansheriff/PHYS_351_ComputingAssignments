/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 22-Feb-2020
 */

// evolve.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "evolve.h"
#include "forces.h"
#include "params.h"
#include "vector_mtx.h"
#include "analysis.h"

void RecordAStep(FILE *output, double t_now, double *q, int num_eq);

void EvolveNeq(double *q)
{
// Declare the necessary variables
        int it, it_max, i, num_eq, count;
        double t_now, t_i, h, t_f, t_next, err, tol;
        FuncPt *QVelos; // To pass onto another function
        double *q_next, *q_tmp;
        FILE *output;

        t_i = PARAM_DATA.t_i;
        t_f = PARAM_DATA.t_f;

        if(t_f < t_i) {
                fprintf(stderr, "t_f is smaller than t_i");
                exit(1); //exits the program
        }

        num_eq = PARAM_DATA.num_eq;//set variables
        h = PARAM_DATA.h;
        it_max = PARAM_DATA.it_max;
        QVelos = PARAM_DATA.QVelos;
        q_next = vector_malloc(num_eq);//allocated memory for q

        output = fopen("results.dat", "w"); //open file for writing, write each value

        t_now = t_i;//set this to start

        for(it=0; it<it_max; it++)
        {
// Record the dynamic variables at t_now
                RecordAStep(output, t_now, q, num_eq);

// This is where actual RK4 evolution takes place
                RK4Step(q, q_next, QVelos, t_now, h, num_eq);

                q_tmp = q; //set the next variables as the current variables
                q = q_next;
                q_next = q_tmp;
                t_now = t_now + h;
        }// it-loop

        RecordAStep(output, t_now, q, num_eq); // Results at t_f

        fclose(output);

        return;
}// EvolveNeq


void RecordAStep(FILE *output, double t_now, double *q, int num_eq)
{

        double ene;
        ene = KineticEnergy(q); // KineticEnergy should be in analysis.c

// ** In the output file, write a new line containing the numerical values of
// t_now q[0] ... q[num_eq-1] ene

        fprintf(output,"%f, ",t_now);

        for (int t = 0; t < num_eq; t++) {
                fprintf(output,"%f, ",q[t]);
        }
        fprintf(output, "%f\n",ene);
        //fprintf(output, "%f, %f, %f, %f, %f\n", t_now, q[1], q[2], q[0], ene);//outputs all t_now, q[1], q[2], q[0], ene to results file

        return;
}// RecordAStep


void OneStepNeq
        (double *q_now, double *q_in, double *q_next, FuncPt *QVelos, double t_in,
        double h, int num_eq)
{

        for (int i = 0; i < num_eq; i++) {
                q_next[i] = q_now[i] + h*(*QVelos[i])(q_in, t_in, num_eq);//sets q_next depending on force
        }
        return;
}// OneStepNeq


void RK4Step
        (double *q, double *q_next, FuncPt *QVelos, double t_now, double h, int num_eq)
{
        int n;
        double t_half, t_next;
        static int ind = 0;
        static double *q_local, *q_sum;

        ind++; // this counts how many times this function is called

        if(ind == 1) // this is the first time this function is called
        {

                q_local = vector_malloc(num_eq);
                q_sum = vector_malloc(num_eq);

        }

        t_half = t_now + (h/2);
        t_next = t_now + h;

//initialize q_sum to 0
        Vector_Clear(q_sum, num_eq);

// RK 1rst step.
        OneStepNeq(q, q, q_local, QVelos, t_now, 0.5*h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);

// RK second step. Backward-Euler-like half step
        OneStepNeq(q, q_local, q_next, QVelos, t_half, 0.5*h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_next, 2.0/3.0, num_eq);

//RK third step
        OneStepNeq(q, q_next, q_local, QVelos, t_half, h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);//add 1/3 of the third vector to q_sum

//RK fourth step
        OneStepNeq(q, q_local, q_next, QVelos, t_next, h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_next, 1.0/6.0, num_eq);//add 1/6 of the fourth vector to q_sum
        Vector_APlusScaledBtoA(q_sum, q, -1.0/2.0, num_eq);//add -1/2 of q to q_sum

        Vector_Copy(q_sum, q_next, num_eq);//copies final q_sum to q_next

        return;
}// RK4Step
