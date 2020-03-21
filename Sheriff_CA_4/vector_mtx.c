/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   20-Feb-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 05-Mar-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"

double *vector_malloc(int nmax){ //memory allocation for a vector
        double *v;
        v = (double *) malloc(sizeof(double)*nmax);
        return v;
}

double **mtx_malloc(int mmax, int nmax){ //memory allocation for a matrix
        double **mtx;
        mtx = (double**)malloc(sizeof(double*)*mmax);

        for(int m=0; m<mmax; m++) {
                mtx[m] = (double *)malloc(sizeof(double)*nmax);
        }

        return mtx;
}

void mtx_free(double **mtx, int mmax){ //memory de-allocation for a matrix
        for(int m=0; m<mmax; m++) {
                free(mtx[m]);
        }
        free(mtx);
}

void Vector_Copy(double *a, double *b, int nmax){ //Copy one vector to another
        for(int i=0; i< nmax; i++) {
                b[i]=a[i];
        }
}

int *int_vector_malloc(int nmax){ //memory allocation for a vector with integer data
        int *v = (int *) malloc(sizeof(int)*nmax);
        return v;

}

void Vector_APlusScaledBtoA(double *a, double *b, double c, int num_eq){ //calculates A+c*B
        for(int i = 0; i < num_eq; i++) {
                a[i] = a[i] + c*b[i];
        }
        return;
}


void Vector_Clear(double *a, int num_eq){ //clears a vector
        for (int i = 0; i< num_eq; i++) {
                a[i] = 0;
        }
        return;
}
double Vector_Distance(double *a, double *b, int num_elems){//gets distance between vectors
        double temp,d;
        d=0;
        for(int i=0; i< (num_elems); i++) {
                temp= pow((a[i]-b[i]),2);
                d += temp;
        }
        d=pow(d,0.5);
        return d;
}
