//
// Created by danie on 11-6-2020.
//

#ifndef MTPS3D_RNG_H
#define MTPS3D_RNG_H

#include <random>
#include <functional>

namespace dasl
{

    extern std::mt19937 rng;
    extern std::uniform_real_distribution<> distr;
    extern std::function<double (void)> mt_rng;
    extern std::normal_distribution<> n_distr;
    extern std::function<double (void)> norm_rng;
}



#endif //MTPS3D_RNG_H
