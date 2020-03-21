/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   19-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 19-Jan-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "params.h"
void ReadInParams(char *input_file)
{
        double m;
        double xi;
        double pi;
        double ti;
        double tf;
        int intm;
        double step;
        int nb_order;
        FILE *input; //file pointer

        input = fopen(input_file, "r"); //open the file for reading


        // Reading data from the file which is comma separated (ie: the variables are given in lines by m, xi, pi, etc.)
        fscanf(input, "%lf%*c %lf%*c %lf%*c %lf%*c %lf%*c %d%*c %d", &m, &xi, &pi, &ti, &tf, &intm, &nb_order );

        // Assigning values
        PARAM_DATA.mass = m;
        PARAM_DATA.x_i = xi;
        PARAM_DATA.p_i = pi;
        PARAM_DATA.t_i = ti;
        PARAM_DATA.t_f = tf;
        PARAM_DATA.it_max = intm;
        PARAM_DATA.num_eq = nb_order;

        // Calculating time step h = (t_f-t_i)/it_max and storing it
        step = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max);
        PARAM_DATA.h = step;

        fclose(input);
        return;
}  // ReadInParams


void PrintParams(void)
{
        FILE * fPtr; // File pointer to hold reference to our file

        // Opening the file for writing data
        fPtr = fopen("/Users/Killian/Documents/OneDrive/Homeworks/WINTER_2020/PHYS_351/Sheriff_CA_1/InitParams.dat", "w");


        /* fopen() return NULL if last operation was unsuccessful */
        if(fPtr == NULL)
        {
                /* File not created hence exit */
                printf("Unable to create file.\n");
                exit(EXIT_FAILURE);
        }

        // Printing the values of our variables to the file
        fprintf(fPtr, "Mass: %lf kg\n", PARAM_DATA.mass);
        fprintf(fPtr, "Initial Position: %lf m\n", PARAM_DATA.x_i);
        fprintf(fPtr, "Initial Momentum: %lf kg*m/s\n", PARAM_DATA.p_i);
        fprintf(fPtr, "Initial Time: %lf s\n", PARAM_DATA.t_i);
        fprintf(fPtr, "Final Time: %lf s\n", PARAM_DATA.t_f);
        fprintf(fPtr, "Number of Time Intervals: %d\n", PARAM_DATA.it_max);
        fprintf(fPtr, "Time Step Size: %lf s\n", PARAM_DATA.h);
        fprintf(fPtr, "Number of 1st order equations: %d\n", PARAM_DATA.num_eq);

        fclose(fPtr);
}   // PrintParams
