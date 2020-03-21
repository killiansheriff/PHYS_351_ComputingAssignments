/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 20-Feb-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "params.h" // parameter definitions
#include "init.h" // initialization functions
#include "evolve.h" // time evolution

int main(int argc, char **argv)
{
        char *input_file; // Input file name
        double *q;
        double t_i, t_f;

        input_file = argv[1]; //gets input file from terminal

        ReadInParams(input_file);
        PrintParams(); //prints parameters

        q = vector_malloc(PARAM_DATA.num_eq); //allocated memory for q

        InitializeNeq(q); //initializes q
        EvolveNeq(q); //evolves q

        return 0;
} // main
