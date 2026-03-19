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

    void SetVolume(int v) { volume = std::clamp(v, 0, 100); }
    int GetVolume() const { return volume; }

private:
    Settings() = default;
    bool isFullscreen = false;

    int volume = 100;
};