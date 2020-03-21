/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 22-Feb-2020
 */

// init.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "forces.h"
#include "init.h"
#include "vector_mtx.h"

void ReadInParams(char *input_file)
{
        FILE *input; // Order of reading-in: num_eq, qi[0],qi[1],qi[2], t_i, t_f, it_max,choice, I_prin[0],I_prin[1],I_prin[2]
        input = fopen(input_file, "r");//open file for reading

        fscanf(input, "num_eq = %d", &PARAM_DATA.num_eq); //get value for number of equations
        PARAM_DATA.q_i = vector_malloc(PARAM_DATA.num_eq); //assigns memory for the q_i vector
        PARAM_DATA.I_prin = vector_malloc(PARAM_DATA.num_eq); //assigns memory for the I_prin vector

        for(int i = 0; i < PARAM_DATA.num_eq; i++) { //assigns each q_i value
                fscanf(input, "\nq_i[%*c] = %lf", &PARAM_DATA.q_i[i]);
        }

        fscanf(input, "\nt_i = %lf", &PARAM_DATA.t_i); //assigns the rest of the variables
        fscanf(input, "\nt_f = %lf", &PARAM_DATA.t_f);
        fscanf(input, "\nit_max = %d", &PARAM_DATA.it_max);
        fscanf(input, "\nh = %lf", &PARAM_DATA.h);

        for(int i = 0; i < PARAM_DATA.num_eq; i++) { //assigns each I_prin value
                fscanf(input, "\nI_prin[%*c] = %lf", &PARAM_DATA.I_prin[i]);
        }

        PARAM_DATA.h = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max); //time step

        fclose(input); //close file


        return;

}// ReadInParams


void PrintParams(void)
{
        FILE *output;// Order of reading-out: mass, x_i, p_i, t_i, t_f, it_max, num_eq, k_spring
        output = fopen("params.dat", "w"); //open file for writing

        fprintf(output, "Number of Diff Equations %d\n", PARAM_DATA.num_eq);

        for(int i = 0; i < PARAM_DATA.num_eq; i++) { //prints each qi
                fprintf(output, "q_i[%d] = %lf\n", i, PARAM_DATA.q_i[i]);
        }

        fprintf(output, "Initial Time %e\n", PARAM_DATA.t_i);
        fprintf(output, "Final Time %e\n", PARAM_DATA.t_f);
        fprintf(output, "Number of Time Intervals %d\n", PARAM_DATA.it_max);
        fprintf(output, "Time Step Size %e\n", PARAM_DATA.h);

        for(int i = 0; i < PARAM_DATA.num_eq; i++) {//print each I
                fprintf(output, "I_prin[%d] = %lf\n", i, PARAM_DATA.I_prin[i]);
        }

        fclose(output);//close files
        return;
}// PrintParams

// Initialized the q vector
void InitializeNeq(double *q)
{

        for(int i = 0; i < PARAM_DATA.num_eq; i++) {//assigns each q_i value
                q[i] = PARAM_DATA.q_i[i];
        }
        PARAM_DATA.QVelos = (FuncPt *)malloc(sizeof(FuncPt)*PARAM_DATA.num_eq);
        PARAM_DATA.QVelos[0] = QVelo0;//assigns QVelos
        PARAM_DATA.QVelos[1] = QVelo1;
        PARAM_DATA.QVelos[2] = QVelo2;
        return;
}// IntializeNeq
