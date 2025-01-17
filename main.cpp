#include <iostream>

void matrix_vector(int rows, int cols, double* A, double* v, double* out) {
    for(int r=0; r<rows; r++) {
        double rowSum = 0;
        for(int c=0; c<cols; c++) {
            rowSum += *(A+cols*r+c) * *(v+c);
            std::cout << "r:" << r << " c:" << c << " i:" << cols*r+c << " " << *(A+r+c) << " " << *(v+c) << std::endl;
        }
        *(out+r) = rowSum;
    }
}

void matrix_matrix(int Arows, int Acols, int Bcols, double* A, double* B, double* out) {
    for(int c=0; c<Bcols; c++) {
        // extract column from B
        double v[Acols];
        for(int i=0; i<Acols; i++) {
            int iB = Bcols*c+i;
            v[i] = B[iB];
        }

        double outCol[Arows];
        matrix_vector(Arows, Acols, A, v, outCol);
    }
}

void test() {
    // MATLAB variables for validating matrix*vector
    // A = [1 2 3; 4 5 6; 7 8 9; 10 11 12]
    // v = [1; 2; 3]
    // expected output 14 32 50 68
    std::cout << "Running test code" << std::endl;
    double A[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double v[3] = {1, 2, 3};
    double o[3] = {0, 0, 0};

    matrix_vector(4, 3, A, v, o);

    std::cout << o[0] << " " << o[1] << " " << o[2] << " " << o[3] << std::endl;
}

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cout << "USAGE: " << argv[0] << " <matrix A file> <matrix B file> <operation flag (0 matrix-vector, 1 matrix-matrix)>" << std::endl;
    test();
    return 0;
  }
}