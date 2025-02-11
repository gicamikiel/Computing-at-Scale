#include <cmath>
#include <iostream>

#include "scalarfunction.hpp"
#include "integrationrule.hpp"
#include "integrationrules.hpp"

// quick and dirty, probably no good for everything
double relative_error(double a, double b) {
    return fabs(a-b) / (fabs(a) + fabs(b));
}

// ***** Function class unit tests *****
int test_polynomial_zero(double tol) {
    PolynomialFunction justzero;
    std::cout << "Test if f(x) = 0 at x = 0\n";
    double result = justzero(0);
    std::cout << "result: " << result << "\n\n";
    return relative_error(result, 0) > tol;
}

int test_polynomial_one(double tol) {
    PolynomialFunction justx{{{1,1}}};
    std::cout << "Test if f(x) = x = 1 at x = 1\n";
    double result = justx(1);
    std::cout << "result: " << result << "\n\n";
    return relative_error(result, 1) > tol;
}

int test_polynomial_lowdegree_roots(double tol) {
    PolynomialFunction lowdegree({1, 0, -1});
    std::cout << "Test if roots of (1-x)(1+x) = 1-x^2 are zero\n";
    double negative_root = lowdegree(-1);
    std::cout << "negative root: " << negative_root << "; ";
    double positive_root = lowdegree(1);
    std::cout << "positive root: " << positive_root << "\n\n";
    return relative_error(negative_root, 0) > tol || relative_error(positive_root, 0) > tol;
}

int test_polynomial_highdegree_assigned(double tol) {
    PolynomialFunction assignme;
    std::cout << "Test if roots of 2*x^61-2 at x=1 are zero\n";
    assignme[61] = 2;
    assignme[0] = -2;
    double result = assignme(1);
    std::cout << "result: " << result << "\n\n";
    return relative_error(result, 0) > tol;
}

int test_polynomial_highdegree_dict(double tol) {
    PolynomialFunction constructme({{0,-2.0}, {1521,2.0}});
    std::cout << "Test if roots of 2*x^1521-2 at x=1 are zero\n";
    double result = constructme(1);
    std::cout << "result: " << result << "\n\n";
    return relative_error(result, 0) > tol;
}
// ***** End of Function class unit tests *****

// ***** Integration rule classes unit tests *****
int gauss_legendre_tests(PolynomialFunction funcs[], double from, double to, double ans[], double tol) {
    int fails = 0;
    for (int pts = 1; pts <= 4; pts++) {
        // k points can integrate exactly up to degree 2k-1
        for (int deg = 0; deg <= 2*pts-1; deg++) {
            PolynomialFunction func = funcs[deg];
            GaussLegendre rule = gl_rules[pts];
            double result = rule(func, from, to);
            std::cout << "Test if gauss-legendre with " << pts << " points integrates degree " << deg << " exactly \n";
            if(relative_error(result, ans[deg]) > tol) {
                std::cout << "fail with " << result << " vs answer " << ans[deg] << "\n\n";
                fails++;
            } else {
                std::cout << "pass with " << result << "\n\n";
            }
        }
    }
    return fails;
}

int gauss_lobatto_tests(PolynomialFunction funcs[], double from, double to, double ans[], double tol) {
    int fails = 0;
    for (int pts = 3; pts <= 5; pts++) {
        // k points can integrate exactly up to degree 2k-3
        for (int deg = 0; deg <= 2*pts-3; deg++) {
            PolynomialFunction func = funcs[deg];
            GaussLobatto rule = glo_rules[pts];
            double result = rule(func, from, to);
            std::cout << "Test if gauss-lobatto with " << pts << " points integrates degree " << deg << " exactly \n";
            if(relative_error(result, ans[deg]) > tol) {
                std::cout << "fail with " << result << " vs answer " << ans[deg] << "\n\n";
                fails++;
            } else {
                std::cout << "pass with " << result << "\n\n";
            }
        }
    }
    return fails;
}

int chebyshev_tests(PolynomialFunction funcs[], int num_polys, double from, double to, double ans[], double tol) {
    int fails = 0;
    for (int deg=1; deg<num_polys; deg++) {
        PolynomialFunction func = funcs[deg];
        // k points can integrate exactly up to degree 2k-1?
        // for degree ceil((d+1)/2) points needed?
        // https://math.stackexchange.com/questions/4415248/prove-that-int-11-fracfx-sqrt1-x2dx-frac-pin-sum-k-0n
        int pts = ceil((deg+1)/2);
        GaussChebyshev rule{pts*2};
        double result = rule(func, from, to);
        std::cout << "Test if gauss-chebyshev with " << pts << " points integrates degree " << deg << " exactly \n";
        if(relative_error(result, ans[deg]) > tol) {
            std::cout << "fail with " << result << " vs answer " << ans[deg] << "\n\n";
            fails++;
        } else {
            std::cout << "pass with " << result << "\n\n";
        }
    }
    return fails;
}

// ***** End of Integration rule classes unit tests *****

int main(int argc, char** argv) {
    int result = 0;
    double tol = 1e-15;

    std::cout << "***** POLYNOMIAL TESTS *****\n";
    result += test_polynomial_zero(tol);
    result += test_polynomial_one(tol);
    result += test_polynomial_lowdegree_roots(tol);
    result += test_polynomial_highdegree_assigned(tol);
    result += test_polynomial_highdegree_dict(tol);

    int polynomial_result = result;

    double from = 3.0/4.0;
    double to = 9.0/4.0;
    // GL can integrate up to degree 2*k-1 (2*4-1 = 7)
    // max degree needed is 7 (if starting from f(x)=1, 8 total)
    int num_polys = 8;
    PolynomialFunction test_funcs[num_polys];
    test_funcs[0] = PolynomialFunction{{{0,1}}}; // f(x) = 1
    for (int deg=1; deg<num_polys; deg++) {
        test_funcs[deg] = PolynomialFunction{{{0,1}, {deg,1}}}; // f(x) = 1 + x^deg
    }
    double results[num_polys] = {3.0/2, 15.0/4, 165.0/32, 501.0/64, 33243.0/2560, 23649.0/1024, 2476407.0/57344, 1369581.0/16384};

    std::cout << "***** GAUSS-LEGENDRE *****\n";
    int gl_result = gauss_legendre_tests(test_funcs, from, to, results, tol);
    result += gl_result;

    std::cout << "***** GAUSS-LOBATTO *****\n";
    int glo_result = gauss_lobatto_tests(test_funcs, from, to, results, tol);
    result += glo_result;

    std::cout << "***** GAUSS-CHEBYSHEV *****\n";
    int gc_result = chebyshev_tests(test_funcs, num_polys, from, to, results, tol);
    result += gc_result;

    std::cout << "***** RESULT *****\n";
    if (result == 0) {
        std::cout << "All tests passed \n";
    } else {
        std::cout << polynomial_result << " polynomial tests failed \n";
        std::cout << gl_result << " gauss-legendre tests failed \n";
        std::cout << glo_result << " gauss-lobatto tests failed \n";
        std::cout << gc_result << " chebyshev tests failed \n";
    }
    return result;
}