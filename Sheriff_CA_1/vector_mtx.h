/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   12-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 19-Jan-2020
 */

#ifndef VECTOR_MTX_H // (if not defined ...)
#define VECTOR_MTX_H // (define ...)
// These ensure that each header file is included only once
// If this header was previously included by another header
// then VECTOR_MTX_H is already defined.
// In that case, we jump to the last line and skip the content

double *vector_malloc(int nmax); // vector memory allocation
                                 // index runs from 0 to nmax-1

double **mtx_malloc(int mmax, int nmax); // matrix memory allocation
                                         // indices run from 0 to mmax-1
                                         // and 0 to nmax-1

void mtx_free(double **mtx, int mmax); // matrix memory de-allocation

void CopyVector(double *a, double *b, int nmax);
// copy a to b. the index runs from 0 to nmax-1

// integer operations
int *int_vector_malloc(int nmax); // integer vector allocation
#endif // ensures that each header file is included only once
