# Assignment 1
## Build Instructions
1. Navigate into ```assignment1``` directory
2. Run ```cmake -S . -B build``` in the terminal
3. Run ```cmake --build build``` to compile

## Usage
* Run ```build/source/polynomial_integrate``` to get usage information for integrating polynomials in the command line.
    * Usage: `polynomial_integrate <a> <b> <rule> <# points> <c0x0> <c1x1> ... <cnxn>`
        * `<a>` is the lower integration bound
        * `<b>` is the upper integration bound
        * `<rule>` is the integration rule, either 'gauss-legendre', 'gauss-lobatto' or 'gauss-chebyshev'
        * `<# points>` is the number of points evaluated by the integration rule
        * `<cnxn>` are polynomial terms $$c_nx^n$$
            * Any arbitrary number of terms can be defined and the polynomial integrated is the sum of all terms.
    * Example: `polynomial_integrate 0.75 2.25 gauss-legendre 3 5x0 5x1`
        * Corresponds to the estimation of $$\int^{2.25}_{0.75} 5x+5\ dx$$ using 3-point Gauss-Legendre quadrature.

* Run ```build/tests/unit_tests``` to run unit tests.