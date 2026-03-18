#include "SceneModule.h"
#include "Scene.h"


extern unsigned int screenW;
extern unsigned int screenH;

SceneModule::SceneModule()
{
    name = "default";
    window = sf::RenderWindow(sf::VideoMode({ 800, 600 }), "default");
    window.setFramerateLimit(60);
}

SceneModule::SceneModule(sf::Vector2u size, std::string name)
{
    this->name = name;
    window = sf::RenderWindow(sf::VideoMode(size), name);
}

void SceneModule::SetActiveScene(Scene* scene)
{
    activeScene = scene;
    window.setSize(scene->getSize());
    sf::View view(sf::FloatRect(
        { 0.f, 0.f },
        { (float)scene->getSize().x, (float)scene->getSize().y }
    ));
    window.setView(view);
    window.setTitle(name + " : " + scene->getName());
}

Scene* SceneModule::GetActiveScene()
{
    return activeScene;
}

void SceneModule::Start()
{
    InputManager::Initialize(&window);
    if (activeScene != nullptr)
        activeScene->Start();
    Update();
}

void SceneModule::Update()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // F11 — reste dans le moteur, appelle le jeu via callback
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::F11)
                {
                    if (onFullscreenToggle)
                        onFullscreenToggle();
                }
            }
        }

        if (pendingFullscreen)
        {
            pendingFullscreen = false;
            if (pendingFullscreenValue)
                window.create(sf::VideoMode::getDesktopMode(), name, sf::State::Fullscreen);
            else
                window.create(sf::VideoMode({ 1280, 720 }), name, sf::State::Windowed);

            screenW = window.getSize().x;
            screenH = window.getSize().y;
            InputManager::Initialize(&window);

            // Forcer la vue avec les nouvelles dimensions
            sf::View view(sf::FloatRect(
                { 0.f, 0.f },
                { (float)screenW, (float)screenH }
            ));
            window.setView(view);

            // Signaler au jeu de recréer la scène avec les nouvelles dimensions
            if (onFullscreenApplied)
                onFullscreenApplied();
        }


        if (pendingScene != nullptr)
        {
            InputManager::Clear();
            SetActiveScene(pendingScene);
            pendingScene->Start();
            pendingScene = nullptr;
        }

        InputManager::ProcessInput();
        Event::ProcessEvent();
        window.clear();
        if (activeScene != nullptr)
            activeScene->Update(window);
    }
}