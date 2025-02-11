#include <stdexcept>
#include <cmath>

#include "integrationrule.hpp"

double IntegrationRule::operator()(ScalarFunction function, double from, double to) const {return 0;}

GaussLegendre::GaussLegendre(std::vector<double> xi_pts, std::vector<double> weights)
    : xi_pts_(xi_pts), weights_(weights) {}

double GaussLegendre::operator()(ScalarFunction function, double from, double to) const {
    double out = 0;
    for (int i=0; i<num_pts(); i++) {
        out =+ weights_[i]*function(xi_to_x(xi_pts_[i], from, to));
    }
    return dx_dxi(from, to)*out;
}

int GaussLegendre::num_pts() const {
    return xi_pts_.size();
}

double GaussLegendre::dx_dxi(double from, double to) const {
    return (to-from)/2;
}

double GaussLegendre::xi_to_x(double xi, double from, double to) const {
    return (to-from)*xi/2 + (from+to)/2;
}

double GaussLobatto::operator()(ScalarFunction function, double from, double to) const {
    double out = 0;
    for (int i=0; i<num_pts(); i++) { // min number of num_pts is 3
        out =+ weights_[i]*function(xi_to_x(xi_pts_[i], from, to));
    }
    double lbound = function(xi_to_x(-1, from, to));
    double rbound = function(xi_to_x(1, from, to));
    double bounds = 2/num_pts()/(num_pts()-1)*(lbound+rbound);
    return dx_dxi(from, to)*(bounds+out);
}

GaussChebyshev::GaussChebyshev(int num_pts) {
    if(num_pts <= 0) throw std::invalid_argument("Error: cannot have negative number of points");
    num_pts_ = num_pts;
}

// math for arbitrary bounds based on
// https://ice.uchicago.edu/2012_presentations/Faculty/Judd/Quadrature_ICE11.pdf slide 11
double GaussChebyshev::operator()(ScalarFunction function, double from, double to) const {
    double out = 0;
    double coef = M_PI*(to-from)/2/num_pts_;
    for(int i=1; i<=num_pts_; i++) {
        double x_i = std::cos((2*i-1)/2/num_pts_*M_PI);
        out += function((x_i+1)*(to-from)/2+from)*std::sqrt(1-x_i*x_i);
    }
    return coef*out;
}

GaussChebyshev GaussChebyshev::operator++(int) {
    return GaussChebyshev(num_pts_++);
}

GaussChebyshev GaussChebyshev::operator--(int) {
    return GaussChebyshev(num_pts_--);
}