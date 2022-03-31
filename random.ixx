#pragma once
export module random;
import <random>;

export double Random(double lower_bound, double upper_bound)  // Generate Random Number
{
    return ((double)((rand() % RAND_MAX)) / (double)RAND_MAX) *
        (upper_bound - lower_bound) + lower_bound;
};