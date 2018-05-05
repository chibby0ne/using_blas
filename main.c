#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cblas.h>


void print_vector(double *matrix, int cols);
void print_matrix(double *matrix, int rows, int cols);
double *create_vector(int elems);
double *create_matrix(int rows, int cols);
void init_matrix_vector(double *matrix, int num, ...);
int abs(int val);
int adjustment_factor(int i, int rows, int cols);

/**
 * Returns absolute value of val 
 */
int abs(int val)
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
        return -1 * (abs(rows - cols) * i);
    }
    return (abs(rows - cols) * i);
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

void function_name()
{
    
}

int main(int argc, char *argv[])
{
    /* enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102}; */
    /* enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113}; */
    /* enum CBLAS_UPLO {CblasUpper=121, CblasLower=122}; */
    /* enum CBLAS_DIAG {CblasNonUnit=131, CblasUnit=132}; */
    /* enum CBLAS_SIDE {CblasLeft=141, CblasRight=142}; */

    CBLAS_ORDER order = CblasRowMajor;
    CBLAS_TRANSPOSE transA = CblasNoTrans;
    CBLAS_TRANSPOSE transB = CblasNoTrans;
    int m = 2;
    int k = 3;
    int n = 4;
    double alpha = 1;
    double beta = 1;
    double *A = create_matrix(m, k);
    double *B = create_matrix(k, n);
    double *C = create_matrix(m, n);
    double *D = create_matrix(n, k);
    double *x = create_vector(k);
    double *d = create_vector(m);
    printf("A\n");
    init_matrix_vector(A, m * k, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
    print_matrix(A, m, k);
    printf("\nB\n");
    init_matrix_vector(B, k * n, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
            10.0, 11.0);
    print_matrix(B, k, n);
    printf("\nD\n");
    init_matrix_vector(D, n * k, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
            10.0, 11.0);
    print_matrix(D, n, k);
    printf("\nx\n");
    init_matrix_vector(x, k * 1, -2.0, 2.0, 10.0);
    print_vector(x, k);

    /* void cblas_dgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA, */
    /*                  const enum CBLAS_TRANSPOSE TransB, const int M, const int N, */
    /*                  const int K, const double alpha, const double *A, */
    /*                  const int lda, const double *B, const int ldb, */
    /*                  const double beta, double *C, const int ldc); */


    cblas_dgemm(order,
            transA,
            transB, 
            m,
            n,
            k,
            alpha,
            A,
            k,
            B,
            n,
            beta,
            C,
            n);
    printf("\nC = A.dot(B)\n");
    print_matrix(C, m, n);


    printf("\nd = A.dot(x)\n");

    /*
     * dasum takes the sum of the absolute values
     */

    /**
     * ddot dot product between two vectors
     */

    /*
     * dnrm2 Eucledian norm of a vector
     */

    /*
     * dscal scales a vector by a constant
     */

    /*
     * daxpy constant times a vector plus a vector. uses unrolled loops for
     * increments equal to one.
     */

    /* void cblas_dgemv(const enum CBLAS_ORDER order, */
    /*              const enum CBLAS_TRANSPOSE TransA, const int M, const int N, */
    /*              const double alpha, const double *A, const int lda, */
    /*              const double *X, const int incX, const double beta, */
    /*              double *Y, const int incY); */
    cblas_dgemv(order,
            transA, // not transposed
            m,   // rows of a
            k,   // cols of a
            alpha, // scalar to multiply A with 
            A,   //matrix A
            k, // lda: leading dimension of A
            x, // vector x
            1, // incx
            beta, // beta: scalar to multiply y with (0 having y as output)
            d, // vector d (Y in formula)
            1); // incy

    print_vector(d, m);
    return 0;
}
