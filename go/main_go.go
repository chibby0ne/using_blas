package main

/*

#cgo LDFLAGS: -lcblas

#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>

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

*/
import "C"
import "unsafe"

func main() {
	var order C.CBLAS_ORDER = C.CblasRowMajor
	var transA C.CBLAS_TRANSPOSE = C.CblasNoTrans
	var transB C.CBLAS_TRANSPOSE = C.CblasNoTrans

	alpha := C.double(1)
	beta := C.double(1)

	m := C.int(2)
	k := C.int(3)
	n := C.int(4)

	matrixA := []float64{0, 1, 2, 3, 4, 5}
	matrixB := []float64{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
	matrixC := [8]float64{}

	ptrA := unsafe.Pointer(&matrixA[0])
	ptrB := unsafe.Pointer(&matrixB[0])
	ptrC := unsafe.Pointer(&matrixC[0])

	A := (*C.double)(ptrA)
	B := (*C.double)(ptrB)
	C := (*C.double)(ptrC)

	C.print_matrix(A, m, k)
	C.print_matrix(B, k, n)

	C.cblas_dgemm(order,
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
		n)

	C.print_matrix(C, m, n)
}
