#include "Settings.hpp"

bool Settings::showFps = false;
bool Settings::limitFps = true;
i32  Settings::maxFps = 60;
bool Settings::enableLogging = false;
bool Settings::enableSounds = true;

void Settings::load() {
    std::ifstream file("settings.ini", std::ios::in);
    
    std::string buffer;
    while (file) {
        std::getline(file, buffer);

        Settings::parseOption(buffer, "showfps:", Settings::showFps);
        Settings::parseOption(buffer, "limitfps:", Settings::limitFps);
        Settings::parseOption(buffer, "maxfps:", Settings::maxFps);
        Settings::parseOption(buffer, "enablelogging:", Settings::enableLogging);
        Settings::parseOption(buffer, "enablesounds:", Settings::enableSounds);
    }
    file.close();
}

template <typename T>
void Settings::parseOption(std::string& buffer, const std::string& option, T& num) {
    size_t found = buffer.rfind(option);
    if (found != std::string::npos) {
        buffer.replace(found, option.length(), "");
        num = std::stoi(buffer);
    }
}

void Settings::save() {
    std::ofstream file("settings.ini", std::ios::out);
    file << "showfps: " << Settings::showFps << "\n";
    file << "limitfps: " << Settings::limitFps << "\n";
    file << "maxfps: " << Settings::maxFps << "\n";
    file << "enablelogging: " << Settings::enableLogging << "\n";
    file << "enablesounds: " << Settings::enableSounds;
    file.close();
}