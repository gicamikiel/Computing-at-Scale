#include <iostream>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "mmio.h"
}

void matrix_vector(int rows, int cols, double* A, double* v, double* out) {
    for(int r=0; r<rows; r++) {
        double rowSum = 0;
        for(int c=0; c<cols; c++) {
            rowSum += *(A+cols*r+c) * *(v+c);
        }
        *(out+r) = rowSum;
    }
}

void matrix_matrix(int Arows, int Acols, int Bcols, double* A, double* B, double* out) {
    for(int c=0; c<Bcols; c++) {
        // extract column from B
        double v[Acols];
        for(int i=0; i<Acols; i++) {
            int iB = Bcols*i+c;
            v[i] = B[iB];
        }
        // deposit into columns
        double outCol[Arows];
        matrix_vector(Arows, Acols, A, v, outCol);
        for(int i=0; i<Arows; i++) {
            int iOut = Bcols*i+c;
            out[iOut] = outCol[i];
        } 
    }
}

void test() {
    // MATLAB variables for validating matrix*vector
    // A = [1 2 3; 4 5 6; 7 8 9; 10 11 12]; B = [13 14 15 16 17; 18 19 20 21 22; 23 24 25 26 27]; v = [1; 2; 3];
    // expected output 14 32 50 68
    std::cout << "Running test code" << std::endl;
    double A[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double v[3] = {1, 2, 3};
    double o[3] = {0, 0, 0};
    matrix_vector(4, 3, A, v, o);
    std::cout << o[0] << " " << o[1] << " " << o[2] << " " << o[3] << std::endl;

    double B[15] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
    double O[20];
    matrix_matrix(4, 3, 5, A, B, O);
    // expected output 118 124 130 136 142 280 295 310 325 340 442 466 490 514 538 604 637 670 703 736
    for(int i=0; i<20; i++) std::cout << O[i] << " ";
    std::cout << std::endl;
}

int allocate_matrix(FILE *f, int rows, int cols, int entries, double* out) {
    int * I = new int[entries];
    int * J = new int[entries];
    double * val = new double[entries];
    MM_typecode matcode;
    if(mm_read_mtx_crd_data(f, rows, cols, entries, I, J, val, matcode) != 0) return 1;
    for(int i=0; i<entries; i++) out[cols*I[i]+J[i]] = val[i];
    delete[] I;
    delete[] J;
    delete[] val;
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout << "USAGE: " << argv[0] << " <matrix A file> <matrix B file> <operation flag (0 matrix-vector, 1 matrix-matrix)>" << std::endl;
        test();
        return 0;
    }

    // loading files
    FILE *fA;
    if ((fA = fopen(argv[1], "r")) == NULL) return 1;
    int rowsA = 0;
    int colsA = 0;
    int entriesA = 0;
    if (mm_read_mtx_crd_size(fA, &rowsA, &colsA, &entriesA) !=0) return 1;
    std::cout << "File A stats: " << colsA << " columns " << rowsA << " rows " << entriesA << " entries" << std::endl;

    FILE *fB;
    if ((fB = fopen(argv[1], "r")) == NULL) return 1;
    int rowsB = 0;
    int colsB = 0;
    int entriesB = 0;
    if (mm_read_mtx_crd_size(fB, &rowsB, &colsB, &entriesB) !=0) return 1;
    std::cout << "File B stats: " << colsB << " columns " << rowsB << " rows " << entriesB << " entries" << std::endl;

    // allocate arrays
    double * arrayA = new double[entriesA];
    allocate_matrix(fA,rowsA,colsA,entriesA,arrayA);
    double * arrayB = new double[entriesB];
    allocate_matrix(fB,rowsB,colsB,entriesB,arrayB);
    double * result;

    int out = 0;
    if (atoi(argv[3]) == 0) {
        // matrix-vector
        std::cout << "Performing matrix-vector operation" << std::endl;
        result = new double[entriesB];
        matrix_vector(rowsA, colsA, arrayA, arrayB, result);
    } else if (atoi(argv[3]) == 1) {
        // matrix-matrix
        std::cout << "Performing matrix-matrix operation" << std::endl;
        int resultRows = rowsA;
        int resultCols = colsB;
        result = new double[resultRows * resultCols];
        matrix_matrix(rowsA, colsA, colsB, arrayA, arrayB, result);
    } else {
        std::cout << "Unknown operation flag" << std::endl;
        out = 1;
    }

    delete[] result;
    delete[] arrayA;
    delete[] arrayB;
    return out;
}