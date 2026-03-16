#pragma once
#include <SFML/Graphics.hpp>

extern unsigned int screenW;
extern unsigned int screenH;

class Settings {
public:
    static Settings& GetInstance() {
        static Settings instance;
        return instance;
    }

    void ToggleFullscreen();
    bool IsFullscreen() const { return isFullscreen; }

private:
    Settings() = default;
    bool isFullscreen = false;
};