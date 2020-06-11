//
// Created by danie on 11-6-2020.
//

#include "RNG.h"

#include "RNG.h"
#include <random>
#include <time.h>


namespace dasl
{
    //std::mt19937 rng(std::random_device{}());
    std::mt19937 rng(time(0));

    std::uniform_real_distribution<> distr(0, 1);
    std::function<double (void)> mt_rng = std::bind(distr,rng);
    std::normal_distribution<> n_distr(0, 1);
    std::function<double (void)> norm_rng = std::bind(n_distr, rng);
}