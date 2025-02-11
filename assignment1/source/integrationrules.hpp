#include <map>
#include <string>
#include <cmath>

#include "integrationrule.hpp"

#define KEY(idx, pts) std::make_pair(names[ idx ], pts )
#define HI_WT_PT std::sqrt(3/7 - 2/7*std::sqrt(6/5))
#define HI_WT (18+std::sqrt(30))/36
#define LOW_WT_PT std::sqrt(3/7 + 2/7*std::sqrt(6/5))
#define LOW_WT (18-std::sqrt(30))/36

std::string names[2] = {"gauss-legendre", "gauss-lobatto"};
std::map<std::pair<std::string, int>, IntegrationRule> rules {
    {KEY(0,1), GaussLegendre({0}, {2})},
    {KEY(0,2), GaussLegendre({-1/std::sqrt(3), 1/std::sqrt(3)}, {1, 1})},
    {KEY(0,3), GaussLegendre({-std::sqrt(3/5), 0, std::sqrt(3/5)}, {5/9, 8/9, 5/9})},
    {KEY(0,4), GaussLegendre({-LOW_WT_PT, -HI_WT_PT, HI_WT_PT, LOW_WT_PT}, {LOW_WT, HI_WT, HI_WT, LOW_WT})},
    {KEY(1,3), GaussLobatto({-1, 0, 1},{1/3, 4/3, 1/3})},
    {KEY(1,4), GaussLobatto({-1, -std::sqrt(1/5), std::sqrt(1/5), 1},{1/6, 5/6, 5/6, 1/6})},
    {KEY(1,5), GaussLobatto({-1, -std::sqrt(3/7), 0, std::sqrt(3/7), 1},{1/10, 49/90, 32/45, 49/90, 1/10})}
};

#undef KEY
#undef HI_WT
#undef HI_WT_PT
#undef LOW_WT
#undef LOW_WT_PT

/*
rules[std::make_pair(names[0],3)] = 
rules[std::make_pair(names[0],4)] = 
rules[std::make_pair(names[0],5)] = 
*/