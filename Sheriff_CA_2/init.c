/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   25-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 29-Jan-2020
 */

// This file is init.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "init.h"
#include "forces.h"
void ReadInParams_Not_Modified(char *input)
{
// You have already implemented this in assignment 1
// Here is my implementation
        double x;
        int ix;
        FILE *input_file;
// Order of reading-in:
// mass, x_i, p_i, t_i, t_f, it_max, choice, num_eq, k_spring

        input_file = fopen(input, "r");
// mass of the particle
        fscanf(input_file, "%lf", &x);
        PARAM_DATA.mass = x;
// initial position and momentum
        fscanf(input_file, "%lf", &x);
        PARAM_DATA.x_i = x;
        fscanf(input_file, "%lf", &x);
        PARAM_DATA.p_i = x;
// initial time, final time, number of steps, time step size
        fscanf(input_file, "%lf", &x);
        PARAM_DATA.t_i = x;
        fscanf(input_file, "%lf", &x);
        PARAM_DATA.t_f = x;
        fscanf(input_file, "%d", &ix);
        PARAM_DATA.it_max = ix;

        x = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max);
        PARAM_DATA.h = x;
// Algorithm choice
        fscanf(input_file, "%d", &ix);
        PARAM_DATA.choice = ix;
// Number of equations -- not yet used
        fscanf(input_file, "%d", &ix);
        PARAM_DATA.num_eq = ix;
// spring constant
        fscanf(input_file, "%lf", &x);
        PARAM_DATA.k_spring = x;

        fclose(input_file);
        return;
}// ReadInParams

void ReadInParams(char *input_file){
    FILE *input; // Order of reading-in: mass, x_i, p_i, t_i, t_f, it_max,choice, num_eq, k_spring
    input = fopen(input_file, "r");//open file for reading, read all values
    fscanf(input, "mass = %lf", &PARAM_DATA.mass);
    fscanf(input, "\nx_i = %lf", &PARAM_DATA.x_i);
    fscanf(input, "\np_i = %lf", &PARAM_DATA.p_i);
    fscanf(input, "\nt_i = %lf", &PARAM_DATA.t_i);
    fscanf(input, "\nt_f = %lf", &PARAM_DATA.t_f);
    fscanf(input, "\nit_max = %d", &PARAM_DATA.it_max);
    fscanf(input, "\nchoice = %d", &PARAM_DATA.choice);
    fscanf(input, "\nnum_eq = %d", &PARAM_DATA.num_eq);
    fscanf(input, "\nspring const k = %lf", &PARAM_DATA.k_spring);
    PARAM_DATA.h = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max);//calculate h
    fclose(input);//close files
    return;
}


void PrintParams(void)
{
// You have already implemented this in assignment 1
// Here is my implementation
        double x;
        int ix;
// Order of reading-in:
// mass, x_i, p_i, t_i, t_f, it_max, h, choice, num_eq, k_spring
        x = PARAM_DATA.mass;
        printf("mass = %e\n", x);
        x = PARAM_DATA.x_i;
        printf("x_i = %e\n", x);
        x = PARAM_DATA.p_i;
        printf("p_i = %e\n", x);
        x = PARAM_DATA.t_i;
        printf("t_i = %e\n", x);
        x = PARAM_DATA.t_f;
        printf("t_f = %e\n", x);
        ix = PARAM_DATA.it_max;
        printf("it_max = %d\n", ix);
        x = PARAM_DATA.h;
        printf("h = %e\n", x);
        ix = PARAM_DATA.choice;

        printf("choice = %d\n", ix);
        ix = PARAM_DATA.num_eq;
        printf("num_eq = %d\n", ix);
        x = PARAM_DATA.k_spring;
        printf("spring const k = %e\n", x);
        return;
}// PrintParams


// *** TASK ***
// Implement the following function
void Initialize(double *x, double *p)
{
        double x_i, p_i, h;
        int choice;


// Get choice, h, x_i, p_i from PARAM_DATA

        x_i = PARAM_DATA.x_i; //get values from params
        p_i = PARAM_DATA.p_i;
        h = PARAM_DATA.h;
        choice = PARAM_DATA.choice;

        if(choice == 3) // Leapfrog 1: x[0] = x(h/2)
        {
    // Leapfrog 1
    // Implement
            p[0] = p_i;
            x[0] = x_i + (h/2.0)*Velocity(p_i);


        }
        else if(choice == 4) // Leapfrog 2: p[0] = p(h/2)
        {
// Leapfrog 2
// Implement
            x[0] = x_i;
            p[0] = p_i + (h/2.0)*Force(x_i);
        }
        else
        {
// For all other methods

// Implement
            x[0] = x_i;
            p[0] = p_i;
        }
        return;
}// Initialize
