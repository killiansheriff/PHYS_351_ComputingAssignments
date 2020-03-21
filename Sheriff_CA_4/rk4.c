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
#include "forces.h"
#include "params.h"
#include "vector_mtx.h"
#include "rk4.h"

void OneStepNeq(double *q_now, double *q_in, double *q_next, FuncPt *QVelos, double t_in, double h, int num_eq){
        for (int i = 0; i < num_eq; i++) {
                q_next[i] = q_now[i] + h*(*QVelos[i])(q_in, t_in, num_eq);
        }
        return;
}

void RK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, double h, int num_eq){
        int n;
        double t_half, t_next;
        static int ind = 0;
        static double *q_local, *q_sum;
        ind++;

        if(ind == 1) {// for first time function is called
                q_local = vector_malloc(num_eq);
                q_sum = vector_malloc(num_eq); // allocated memory
        }
        t_half=t_now+h/2;
        t_next=t_now+h;

        Vector_Clear(q_sum, num_eq);
        OneStepNeq(q, q, q_local, QVelos, t_now, 0.5*h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);//add 1/3 of the first vector to q_sum

        OneStepNeq(q, q_local, q_next, QVelos, t_half, 0.5*h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_next, 2.0/3.0, num_eq);//add 2/3 of the second vector to q_sum for q**_n+1/2 term

        OneStepNeq(q, q_next, q_local, QVelos, t_half, h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);//add 1/3 of the third vector to q_sum

        OneStepNeq(q, q_local, q_next, QVelos, t_next, h, num_eq);
        Vector_APlusScaledBtoA(q_sum, q_next, 1.0/6.0, num_eq);//add 1/6 of the fourth vector to q_sum q**_n+1

        Vector_APlusScaledBtoA(q_sum, q, -1.0/2.0, num_eq);//add -1/2 of q to q_sum q_n

        Vector_Copy(q_sum, q_next, num_eq);
        return;
}

double AdaptiveRK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, double *t_next,
                       double h, int num_eq){
        double *q_full_1,*q_half;
        double err,half,t_temp;
        q_full_1=vector_malloc(num_eq);
        q_half=vector_malloc(num_eq);
        RK4Step(q, q_full_1, QVelos, t_now, h, num_eq); // q to q_full_1 step h

        half=h/2;
        RK4Step(q, q_half, QVelos, t_now, half, num_eq); // q_full_1 to q_half step h/2
        t_temp=t_now+h/2;
        RK4Step(q_half, q_next, QVelos, t_temp, half, num_eq); // q_half to q_next step h/2

        err = EstimateError(q_full_1, q_next, t_now, h, num_eq);

        *t_next=t_now+h;

        free(q_full_1);
        free(q_half);

        return err;
}

double EstimateError(double *q_full, double *q_next, double t_now, double h, int num_eq){// calulating the error
        double diff;
        diff=Vector_Distance(q_full, q_next, num_eq);
        diff /= 15;
        return diff;
}

double EstimateNextH(double err, double err0, double h){// estimate of the time step size
        double fac,H,temp;
        fac = 0.5;
        temp = fac*err0;
        temp /= err;
        H=h*pow(temp,0.2);
        return H;
}
