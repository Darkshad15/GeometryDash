#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "Scenes.h"
int main()
{
    Engine engine({ 800, 600 }, "Mon Premier Jeu");
    Scenes sc;
    Scene* menu = sc.CreateMain();
    engine.getSceneModule()->SetActiveScene(menu);

    engine.Start();

    return 0;

}