#include <iostream>
#include <string>
using namespace std;

#include "scalarfunction.hpp"
#include "integrationrule.hpp"
#include "integrationrules.hpp"

void display_help() {
    std::cout << "usage: polynomial_integrate <a> <b> <rule> <# points> <c0x0> <c1x1> ...\n";
    std::cout << "      where rule is 'gauss-legendre', 'gauss-lobatto' or 'gauss-chebyshev' and \n";
    std::cout << "      each term of format cnxn represents polynomial term c_n*x^n\n";
}

int main(int argc, char *argv[])
{
    if (argc < 5) {
        display_help();
        return 0;
    }

    std::string from_s(argv[1]);
    double from = stod(from_s);
    std::string to_s(argv[2]);
    double to = stod(to_s);
    std::string rulename(argv[3]);
    std::string num_pts_s(argv[4]);
    int num_pts = stoi(num_pts_s);

    PolynomialFunction p;
    for (int i=5; i<argc; i++) {
        std::string term(argv[i]);
        int pos = term.find_first_of('x');
        double coef = stod(term.substr(0,pos));
        double exp = stoi(term.substr(pos+1));
        p[exp] += coef;
    }

    IntegrationRule* rule;
    if(num_pts < 1) {
        std::cout << "At least one point needed\n";
        return 1;
    }
    GaussChebyshev gc(num_pts);
    if(rulename == "gauss-legendre") {
        if(num_pts > 4) {
            std::cout << "Only 1-4 points are supported\n";
            return 1;
        }
        rule = &gl_rules[num_pts];
    } else if (rulename == "gauss-lobatto") {
        if(num_pts > 5 || num_pts < 3) {
            std::cout << "Only 3-5 points are supported\n";
            return 1;
        }
        rule = &glo_rules[num_pts];
    } else if (rulename == "gauss-chebyshev") {
        rule = &gc;
    } else {
        std::cout << "Invalid rule name\n";
    }

    double out = (*rule)(p, from, to);
    std::cout << out << "\n";
}