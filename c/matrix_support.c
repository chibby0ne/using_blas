#include "matrix_support.h"

/**
 * Returns absolute value of val 
 */
int abs_int(int val)
{
    return val >= 0 ? val : -1 * val;
}

/**
 * Used for printing all the matrices correctly, given that arrays indeces start at 0
 * and matrices/vectors indeces start at 1 and are represented as a 1D array in
 * memory.
 */
int adjustment_factor(int i, int rows, int cols)
{
    if (i == 0) {
        return 0;
    }
    if (rows > cols) {
        return -1 * (abs_int(rows - cols) * i);
    }
    return (abs_int(rows - cols) * i);
}

/**
 * Prints matrix in row major notation
 */
void print_matrix(double *matrix, int rows, int cols)
{
    int index;
    printf("rows: %d, cols: %d\n", rows, cols);
    for (int i = 0; i < rows; ++i) {
        printf("[ ");
        for (int j = 0; j < cols; ++j) {
            index = i * rows + j + adjustment_factor(i, rows, cols);
            printf("%.2f ", matrix[index]);
        }
        printf("]\n");
    }
}

/**
 * Prints vector as column vector
 */
void print_vector(double *matrix, int rows)
{
    print_matrix(matrix, rows, 1);
}


/**
 * Creates a column vector with dimensions (elems) whose elemens are initialized
 * to zero
 */
double *create_vector(int elems)
{
    double *matrix = (double *) calloc(elems, sizeof(double));
    if (matrix == NULL) {
        fprintf(stderr, "Coudln't allocate array\n");
        exit(EXIT_FAILURE);
    }
    return matrix;
}

/**
 * Creates a matrix with dimensions (rows, cols) whose elemens are initialized
 * to zero
 */
double *create_matrix(int rows, int cols)
{
    return create_vector(rows * cols);
}

/**
 * Initializes a matrix or a vector with total number of elements num, using the
 * given arguments
 */
void init_matrix_vector(double *matrix, int num, ...)
{
    va_list args;
    double elem;
    va_start(args, num);
    for (int i = 0; i < num; ++i) {
        elem = va_arg(args, double);
        matrix[i] = elem;
    }
    va_end(args);
}
