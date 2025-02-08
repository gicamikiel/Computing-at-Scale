#ifndef ASSIGNMENT1_SCALARFUNC
#define ASSIGNMENT1_SCALARFUNC

#include <unordered_map>
#include <initializer_list>

class ScalarFunction {
    public:
        virtual double operator()(double x) const;
};

class PolynomialFunction : public ScalarFunction {
    private:
        // Avoids need for code to fill array with zeros to define 'sparse' powers like x^5231
        std::unordered_map<int, double> coefs_;

    public:
        // Initialize to function with zero coefficients f(x) = 0
        PolynomialFunction();

        // Initialize using brace-enclosed initializers for small low-order polynomials
        // First element corresponds to x^0
        PolynomialFunction(std::initializer_list<double> coefs_list);
        
        // Can use to initialize polynomial with brace-enclosed key-value pairs
        // Use exponent as key, coefficient as value
        PolynomialFunction(std::unordered_map<int, double> coefs_dict);

        double operator()(double x) const override;
        double& operator[](int exp);
};

#endif //ASSIGNMENT1_SCALARFUNC