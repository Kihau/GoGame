#include "Stats.hpp"

i64 Stats::totalTime = 0;
i64 Stats::ingameTime = 0;
i32 Stats::mouseClicks = 0;

bool Stats::load() {
    std::ifstream file("stats.bin", std::ios::binary);
    if (file) {
        file.read((char*)&Stats::totalTime, sizeof(i64));
        file.read((char*)&Stats::mouseClicks, sizeof(i32));
        file.close();
        return true;
    } 
    file.close();
    return false;
}

void Stats::save() {
    std::ofstream file("stats.bin", std::ios::binary);
    sf::Int64 total;
    file.write((char*)&Stats::totalTime, sizeof(i64));
    file.write((char*)&Stats::mouseClicks, sizeof(i32));
    file.close();
}