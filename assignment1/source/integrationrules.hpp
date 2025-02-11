#include <map>
#include <string>
#include <cmath>

#include "integrationrule.hpp"

// File for defining common quadrature rules

#define HI_WT_PT std::sqrt(3.0/7 - 2.0/7*std::sqrt(6.0/5))
#define HI_WT (18+std::sqrt(30))/36.0
#define LOW_WT_PT std::sqrt(3.0/7 + 2.0/7*std::sqrt(6.0/5))
#define LOW_WT (18-std::sqrt(30))/36.0

std::unordered_map<int, GaussLegendre> gl_rules = {
    {1, GaussLegendre({0}, {2.0})},
    {2, GaussLegendre({-1.0/std::sqrt(3), 1.0/std::sqrt(3)}, {1.0, 1.0})},
    {3, GaussLegendre({-std::sqrt(3.0/5), 0, std::sqrt(3.0/5)}, {5.0/9, 8.0/9, 5.0/9})},
    {4, GaussLegendre({-LOW_WT_PT, -HI_WT_PT, HI_WT_PT, LOW_WT_PT}, {LOW_WT, HI_WT, HI_WT, LOW_WT})}
};

std::map<int, GaussLobatto> glo_rules = {
    {3, GaussLobatto({-1, 0, 1},{1.0/3, 4.0/3, 1.0/3})},
    {4, GaussLobatto({-1, -std::sqrt(1.0/5), std::sqrt(1.0/5), 1},{1.0/6, 5.0/6, 5.0/6, 1.0/6})},
    {5, GaussLobatto({-1, -std::sqrt(3.0/7), 0, std::sqrt(3.0/7), 1},{1.0/10, 49.0/90, 32.0/45, 49.0/90, 1.0/10})}
};

#undef HI_WT
#undef HI_WT_PT
#undef LOW_WT
#undef LOW_WT_PT