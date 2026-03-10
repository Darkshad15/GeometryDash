#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "Elements.h"
int main()
{
    Elements* el = new Elements();
    Engine engine({ 800, 600 }, "Mon Premier Jeu");

    Scene* mainScene = new Scene("Main", { 800, 600 });
    GameObject* carre = el->createBlock();
    

    mainScene->AddGameObject(carre);

    engine.getSceneModule()->SetActiveScene(mainScene);
    mainScene->Start();
    engine.Start();

    return 0;

}