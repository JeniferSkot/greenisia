#include "random.hpp"


std::mt19937& get_coin_rng()
{
    static std::mt19937 generator
        ([](){ return std::random_device(); }()());

    return generator;
}


