#include <iostream>

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

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cout << "USAGE: " << argv[0] << " <matrix A file> <matrix B file> <operation flag (0 matrix-vector, 1 matrix-matrix)>" << std::endl;
    test();
    return 0;
  }
}