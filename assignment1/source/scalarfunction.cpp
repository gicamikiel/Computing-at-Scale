#include <cmath>
#include <stdexcept>
#include <unordered_map>
#include <initializer_list>
#include <iostream>

#include "scalarfunction.hpp"

double ScalarFunction::operator()(double x) const {return 0;}

PolynomialFunction::PolynomialFunction() : coefs_({}) {}

PolynomialFunction::PolynomialFunction(std::unordered_map<int, double> coefs_dict) : coefs_(coefs_dict) {}

PolynomialFunction::PolynomialFunction(std::initializer_list<double> coefs_list) {
    int exp = 0;
    for (double coef : coefs_list) {
        (*this)[exp] = coef;
        exp++;
    }
}

double PolynomialFunction::operator()(double x) const {
    double sum = 0;
    for (const auto [exp, coef] : coefs_) {
        //std::cout << coef << "*" << x << "^ " << exp << " the sum is " << sum << "\n";
        sum += coef*std::pow(x,exp);
    }
    return sum;
}

double& PolynomialFunction::operator[](int exp)  {
    if (exp < 0) throw std::invalid_argument("Error: polynomials cannot have negative exponents");
    return coefs_[exp];
}