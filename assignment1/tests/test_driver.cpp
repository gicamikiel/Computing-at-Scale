#include "scalarfunction.hpp"

int test_scalarfunction_construct_empty() {
    PolynomialFunction justx({1.0, 2.0, 3.0});
    return 0;
}

int main(int argc, char** argv) {
    int result = 0;
    result += test_scalarfunction_construct_empty();
    return result;
}