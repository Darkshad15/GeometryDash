#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"

#include "Level.h"
int main()
{
    
    Engine engine({ 2000, 600 }, "Mon Premier Jeu");

    Scene* mainScene = new Scene("Main", { 2000, 600 });
    
    Level level(1, 1);
    level.Load("level.txt");
    level.Draw(mainScene);

    engine.getSceneModule()->SetActiveScene(mainScene);
    mainScene->Start();
    engine.Start();

    return 0;

}