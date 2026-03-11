#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "InputManager.h"

int main()
{
    Engine engine({ 800, 600 }, "Mon Premier Jeu");
    engine.getSceneModule()->getWindow().setFramerateLimit(60);
    Scene* mainScene = new Scene("Main", { 800, 600 });
    // Initialiser l'InputManager
    InputManager::Initialize(&engine.getSceneModule()->getWindow());
    GameObject* player = new GameObject({100.f,300.f});
    player = createPlayer();
    MovePl(player);
    

    
    
    mainScene->AddGameObject(player);
    // 5. Activer la scène et démarrer
    engine.getSceneModule()->SetActiveScene(mainScene);
    mainScene->Start();
    
    engine.Start();

    return 0;

}