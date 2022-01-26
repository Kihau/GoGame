#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>
#include "Types.hpp"

// Extention class for random number generation
class Random {
private:
    //static u32 seed;

public:
    inline static void init() {
        //Random::seed = time(nullptr);
        srand(time(nullptr));
    }

    inline static void init(u32 seed) {
        //Random::seed = seed;
        srand(seed);
    }

    // Generates number from [0; max]
    inline static i32 next(u32 max) {
        return rand() % (max + 1);
    }

    // Generates number from [min; max]
    inline static i32 next(u32 min, u32 max) {
        if (min > max) 
            return 0;
            
        return rand() % (max + 1 - min) + min;
    }

    // Generates Range values
};

#endif