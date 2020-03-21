/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   25-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 29-Jan-2020
 */
// analysis.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "analysis.h"

void WriteResults(double *x, double *p)
{
        int it, it_max;
        double t, h, x_now, p_now;

        it_max = PARAM_DATA.it_max;//get values from params
        h = PARAM_DATA.h;

        FILE *output;
        output = fopen("result.dat", "w");//set output file as result.dat

        for(it=0; it<it_max; it++)
        {
                t = h*it;
                GetXP(x, p, &x_now, &p_now, it);//use GetXP to get the values of x and p for each evolve types
                fprintf(output, "\n%e  %e %e", t, x_now, p_now);// Write results in output
        }// it-loop
        fclose(output);
        return;
}// WriteResults

void GetXP(double *x, double *p, double *x_now, double *p_now, int it)
{
        int choice, it_max;
        double h;

        // Get choice, it_max and h from PARAM_DATA
        choice = PARAM_DATA.choice;//get values from params
        it_max = PARAM_DATA.it_max;

        if(choice == 3) // Leapfrog 1. x[0] = x(h/2), p[0] = p(0)
        {
                *p_now = p[it];

                if(it == 0)//For it = 0, we use x_i
                {
                        *x_now=PARAM_DATA.x_i;
                }
                else
                {
                        *x_now = (x[it-1]+x[it])/2.0;//go back half a step and get the value there
                }
        }// choice == 3

        else if(choice == 4) // leapfrog 2.
        {
                *x_now = x[it];// x value needs not be touched
                
                if(it == 0)// For it = 0 use p_i
                {
                        *p_now =PARAM_DATA.p_i;
                }
                else
                {
                        *p_now = (p[it-1]+p[it])/2.0;//go back half a step and get the value there
                }
        }// choice == 4
        else
        {
                // for other choices
                *x_now = x[it];
                *p_now = p[it];
        }
        return;
}//GetXP
