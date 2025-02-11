#ifndef ASSIGNMENT1_INTEGRATIONRULE
#define ASSIGNMENT1_INTEGRATIONRULE

#include <vector>

#include "scalarfunction.hpp"

class IntegrationRule {
    public:
        virtual double operator()(ScalarFunction function, double from, double to) const;
};

class GaussLegendre : public IntegrationRule {
    public:
        GaussLegendre(std::vector<double> xi_pts, std::vector<double> weights);

        double operator()(ScalarFunction function, double from, double to) const override;

        int num_pts() const;

    protected: 
        std::vector<double> const xi_pts_;
        std::vector<double> const weights_;

        // for \int_a^b f(x)\,dx \approx \frac{b-a}{2} \sum_{i=1}^n w_i f\left(\frac{b-a}{2}\xi_i + \frac{a+b}{2}\right)
        // (source https://en.wikipedia.org/wiki/Gaussian_quadrature#Gauss%E2%80%)

        // this is \frac{b-a}{2}
        double dx_dxi(double from, double to) const;
        // this is \frac{b-a}{2}\xi_i + \frac{a+b}{2}
        double xi_to_x(double xi, double from, double to) const;
};

class GaussLobatto : public GaussLegendre {
    public:
        using GaussLegendre::GaussLegendre;

        double operator()(ScalarFunction function, double from, double to) const override;
};

class GaussChebyshev : public IntegrationRule {
    public:
        GaussChebyshev(int num_pts);

        double operator()(ScalarFunction function, double from, double to) const override;

        GaussChebyshev operator++(int);

        GaussChebyshev operator--(int);
    private:
        int num_pts_;
};

#endif // ASSIGNMENT1_INTEGRATIONRULE