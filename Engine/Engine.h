#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SceneModule.h"
#include "InputManager.h"
#include <vector>
#include <iostream>
#include <string>
#include "Event.h"

enum class Direction
{
    Up, Down, Left, Right, Focus
};

class Engine
{
private:
    SceneModule* sceneModule;
    static Engine* instance;
    bool GameState;



public:

    //Constructeurs
    Engine();
    Engine(sf::Vector2u size, std::string name);

    //Get
    static Engine* GetInstance() { return instance; }
    SceneModule* getSceneModule() { return sceneModule; }
    bool getGameState() { return GameState; }

    //Set
    void setGameState(bool B) { GameState = B; }

    //Autres
    void Start();
    void Update();
    void ShutDown();
};
