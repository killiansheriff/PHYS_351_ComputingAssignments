/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   13-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 19-Jan-2020
 */
//#include <stdio.h>
 #include <stdlib.h>
 #include "vector_mtx.h"

double *vector_malloc(int nmax){
        double *vect = malloc(nmax * sizeof(double));
        return vect;
}

double **mtx_malloc(int mmax, int nmax){
        double **mtx = malloc(mmax * sizeof(double *));
        for(int i = 0; i < mmax; i++) {
                mtx[i] = malloc(nmax * sizeof(double));
        }

        return mtx;

}

void mtx_free(double **mtx, int mmax){
        for(int i = 0; i < mmax; i++) {
                free((void *)mtx[i]);
        }

        free((void *)mtx);
}


void CopyVector(double *a, double *b, int nmax){
        for(int i = 0; i < nmax; i++)
                b[i]=a[i];
}

int *int_vector_malloc(int nmax){
        int *vect = malloc(nmax * sizeof(int));
        return vect;

}
