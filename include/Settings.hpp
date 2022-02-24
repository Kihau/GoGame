#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <vector>

#include "Types.hpp"

class Settings {
public:
    static bool showFps;
    static bool limitFps;
    static i32 maxFps;
    static bool enableLogging;
    static bool enableSounds;

    static void load();
    static void save();
private:
    template <typename T>
    static void parseOption(std::string&, const std::string&, T&);
    Settings() {}
};

#endif