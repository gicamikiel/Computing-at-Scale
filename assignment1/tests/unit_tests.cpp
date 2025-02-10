#include <cmath>
#include <iostream>

#include "scalarfunction.hpp"

int test_polynomial_zero(double tol) {
    PolynomialFunction justx;
    std::cout << "Test if f(x) = 0 at x = 0\n";
    double result = justx(0);
    std::cout << "result: " << result << "\n\n";
    return fabs(result) > tol;
}

int test_polynomial_lowdegree_roots(double tol) {
    PolynomialFunction lowdegree({1, 0, -1});
    std::cout << "Test if roots of (1-x)(1+x) = 1-x^2 are zero\n";
    double negative_root = lowdegree(-1);
    std::cout << "negative root: " << negative_root << "; ";
    double positive_root = lowdegree(1);
    std::cout << "positive root: " << positive_root << "\n\n";
    return fabs(negative_root) > tol || fabs(positive_root) > tol;
}

int test_polynomial_highdegree_assigned(double tol) {
    PolynomialFunction assignme;
    std::cout << "Test if roots of 2*x^61-2 at x=1 are zero\n";
    assignme[61] = 2;
    assignme[0] = -2;
    double result = assignme(1);
    std::cout << "result: " << result << "\n\n";
    return fabs(result) > tol;
}

int test_polynomial_highdegree_dict(double tol) {
    PolynomialFunction constructme({{0,-2.0}, {1521,2.0}});
    std::cout << "Test if roots of 2*x^1521-2 at x=1 are zero\n";
    double result = constructme(1);
    std::cout << "result: " << result << "\n\n";
    return fabs(result) > tol;
}

int main(int argc, char** argv) {
    int result = 0;
    double tol = 1e-15;
    result += test_polynomial_zero(tol);
    result += test_polynomial_lowdegree_roots(tol);
    result += test_polynomial_highdegree_assigned(tol);
    result += test_polynomial_highdegree_dict(tol);

    if (result == 0) {
        std::cout << "All tests passed \n";
    } else {
        std::cout << result << " tests failed \n";
    }
    return result;
}