#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "Gen.h"
#include "Level.h"
#include "Player.h"
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "InputManager.h"

int main()
{
    
    Engine engine({ 1500, 600 }, "Mon Premier Jeu");

    Scene* mainScene = new Scene("Main", { 1500, 600 });
    
    Gen* gene = new Gen(mainScene);
    Level* level = gene->getLevel();
    engine.getSceneModule()->SetActiveScene(mainScene);
    gene->GenerateLevel();
    gene->DrawAllLevels(mainScene);
    mainScene->Start();

    Event::CreateEvent(-1, [&level]() {
        static sf::Clock clock;
        float deltaTime = clock.restart().asSeconds();
        level->Move(deltaTime);
        });


    engine.Start();
    
    return 0;

}