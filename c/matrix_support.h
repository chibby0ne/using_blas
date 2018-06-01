#ifndef MATRIX_SUPPORT_H
#define MATRIX_SUPPORT_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void print_vector(double *matrix, int cols);
void print_matrix(double *matrix, int rows, int cols);
double *create_vector(int elems);
double *create_matrix(int rows, int cols);
void init_matrix_vector(double *matrix, int num, ...);
int abs_int(int val);
int adjustment_factor(int i, int rows, int cols);

#endif
