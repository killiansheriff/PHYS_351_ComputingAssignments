/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   25-Jan-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 25-Jan-2020
 */

#ifndef ANALYSIS_H
#define ANALYSIS_H
void WriteResults(double *x, double *p);
void GetXP(double *x, double *p, double *x_now, double *p_now, int it);
// this is not needed yet

// double TotalEnergy(double *x, double *p, int it);
#endif
