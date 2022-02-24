#ifndef STATS_H
#define STATS_H

#include <fstream>

#include "SFML/Graphics.hpp"
#include "Types.hpp"

class Stats {
public:
    static i64 totalTime;
    static i64 ingameTime;
    static i32 mouseClicks;

    static bool load();
    static void save();

private:
    Stats() {}
};

#endif