#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
class Scene;
class SceneModule
{
private:
    Scene* activeScene;
    sf::RenderWindow window;
    std::string name;
    Scene* pendingScene = nullptr;
    bool sceneChanged = false;
    bool pendingFullscreen = false;
    bool pendingFullscreenValue = false;
public:
    std::function<void()> onFullscreenToggle = nullptr; // callback F11
    std::function<void()> onFullscreenApplied = nullptr;


    SceneModule();
    SceneModule(sf::Vector2u size, std::string name);

    sf::RenderWindow& getWindow() { return window; }
    Scene* GetActiveScene();

    void SetActiveScene(Scene* scene);
    void SetPendingScene(Scene* scene) { pendingScene = scene; sceneChanged = true; }
    void SetPendingFullscreen(bool fullscreen) {
        pendingFullscreen = true;
        pendingFullscreenValue = fullscreen;
    }

    void Start();
    void Update();
};