/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   05-Mar-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 05-Mar-2020
 */

#ifndef INIT_H
#define INIT_H
#include "params.h"

void ReadInParams(char *input_file);
void PrintParams(void);
void InitializeNeq(double *q);
#endif
