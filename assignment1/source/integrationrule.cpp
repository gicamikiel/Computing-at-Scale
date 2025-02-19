#include <stdexcept>
#include <cmath>

#include "integrationrule.hpp"

double IntegrationRule::operator()(ScalarFunction& function, double from, double to) const {return 0;}

GaussQuadrature::GaussQuadrature() : xi_pts_({}), weights_({}) {}

GaussQuadrature::GaussQuadrature(std::vector<double> xi_pts, std::vector<double> weights)
    : xi_pts_(xi_pts), weights_(weights) {}

double GaussQuadrature::operator()(ScalarFunction& function, double from, double to) const {
    double out = 0;
    for (int i=0; i<num_pts(); i++) {
        //std::cout << weights_[i] << " " << xi_pts_[i] << " wt, xi\n";
        out += weights_[i]*function(xi_to_x(xi_pts_[i], from, to));
        //std::cout << function(xi_to_x(xi_pts_[i], from, to)) << " f eval\n";
    }
    return dx_dxi(from, to)*out;
}

int GaussQuadrature::num_pts() const {
    return xi_pts_.size();
}

double GaussQuadrature::dx_dxi(double from, double to) const {
    //std::cout << (to-from)/2.0 << " dx_dxi\n";
    return (to-from)/2.0;
}

double GaussQuadrature::xi_to_x(double xi, double from, double to) const {
    return (to-from)*xi/2.0 + (from+to)/2.0;
}

GaussChebyshev::GaussChebyshev(int num_pts) {
    if (num_pts <= 0) throw std::invalid_argument("Error: cannot have negative or zero number of points");
    num_pts_ = num_pts;
}

// math for arbitrary bounds based on
// https://ice.uchicago.edu/2012_presentations/Faculty/Judd/Quadrature_ICE11.pdf slide 11
double GaussChebyshev::operator()(ScalarFunction& function, double from, double to) const {
    double out = 0;
    double coef = M_PI*(to-from)/2.0/num_pts_;
    for (int i=1; i<=num_pts_; i++) {
        double x_i = std::cos(M_PI*(2.0*i-1)/2.0/num_pts_);
        out += function((x_i+1)*(to-from)/2.0+from)*std::sqrt(1-x_i*x_i);
    }
    return coef*out;
}   

GaussChebyshev GaussChebyshev::operator++(int) {
    return GaussChebyshev(num_pts_++);
}

GaussChebyshev GaussChebyshev::operator--(int) {
    return GaussChebyshev(num_pts_--);
}