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
#include "init.h"

void ReadInParams(char *input_file){
        FILE *input;
        double q_i[4];
        input = fopen(input_file, "r");//opens file
        fscanf(input, "num_eq = %d", &PARAM_DATA.num_eq);
        PARAM_DATA.q_i = vector_malloc(PARAM_DATA.num_eq);//allocated memory for p_i
        for(int i = 0; i < PARAM_DATA.num_eq; i++) {
                fscanf(input, "\nq_i[%*c] = %lf", &PARAM_DATA.q_i[i]);
        }
        fscanf(input, "\n t_i = %lf", &PARAM_DATA.t_i);//get values
        fscanf(input, "\n t_f = %lf", &PARAM_DATA.t_f);
        fscanf(input, "\n h = %lf", &PARAM_DATA.h);
        fscanf(input, "\n mass1 = %lf", &PARAM_DATA.mass1);
        fscanf(input, "\n length1 = %lf", &PARAM_DATA.length1);
        fscanf(input, "\n mass2 = %lf", &PARAM_DATA.mass2);
        fscanf(input, "\n length2 = %lf", &PARAM_DATA.length2);
        fscanf(input, "\n prec_goal = %lf", &PARAM_DATA.prec_goal);
        fclose(input); // close file
        return;
}

void PrintParams() {
        FILE *output; // opens an output file
        output = fopen("params.dat", "w");
        fprintf(output,"Number of equations: %d\n", PARAM_DATA.num_eq);
        for(int i=0; i<PARAM_DATA.num_eq; i++) {
                fprintf(output, "q %d: %e\n",i,PARAM_DATA.q_i[i]);
        }
        fprintf(output,"Initial time: %lf\n",  PARAM_DATA.t_i);
        fprintf(output,"Final time:  %lf\n", PARAM_DATA.t_f);
        fprintf(output,"Size of time intervals: %lf\n", PARAM_DATA.h);
        fprintf(output,"Mass 1: %lf kg \n", PARAM_DATA.mass1);
        fprintf(output,"Length 1: %lf m \n",PARAM_DATA.length1);
        fprintf(output,"Mass 2: %lf kg \n", PARAM_DATA.mass2);
        fprintf(output,"Length 2: %lf m \n",PARAM_DATA.length2);
        fprintf(output,"Minimum precision: %e\n",PARAM_DATA.prec_goal);
        fclose(output);
        return;
}

void InitializeNeq(double *q){
        for(int i = 0; i < PARAM_DATA.num_eq; i++) {
                q[i] = PARAM_DATA.q_i[i];
        }
        PARAM_DATA.QVelos = (FuncPt *)malloc(sizeof(FuncPt)*PARAM_DATA.num_eq);
        PARAM_DATA.QVelos[0] = QVelo0;
        PARAM_DATA.QVelos[1] = QVelo1;
        PARAM_DATA.QVelos[2] = QVelo2;
        PARAM_DATA.QVelos[3] = QVelo3;
        return;
}
