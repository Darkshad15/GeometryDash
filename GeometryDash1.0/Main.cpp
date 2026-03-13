#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "Gen.h"
#include "Level.h"
#include "Player.h"
#include "InputManager.h"

int main()
{

    Engine engine({ 1500, 600 }, "Mon Premier Jeu");
    engine.getSceneModule()->getWindow().setFramerateLimit(60);
    Scene* mainScene = new Scene("Main", { 1500, 600 });

    Gen* gene = new Gen(mainScene);
    Level* level = gene->getLevel();
    InputManager::Initialize(&engine.getSceneModule()->getWindow());
    GameObject* player;
    player = createPlayer();
    MovePl(player, mainScene);


    mainScene->AddGameObject(player);
    engine.getSceneModule()->SetActiveScene(mainScene);
    gene->GenerateLevel();
    gene->DrawAllLevels(mainScene);
    mainScene->Start();

    Event::CreateEvent(-2, [&level]() {
        static sf::Clock clock;
        float deltaTime = clock.restart().asSeconds();
        level->Move(deltaTime);
        });

    Event::CreateEvent(1, [&level, &player]() {
        // Reset les blocs à leur position de départ
        level->Reset();

        // Reset le joueur
        player->SetPosition({ 200.f, 200.f });
        Variables* var = player->GetComponent<Variables>();
        if (var != nullptr) {
            var->setFloat("velocityY", 0.0f);
            var->setFloat("isGrounded", 0.0f);
        }
        player->setActive(true);
        });
    engine.Start();

    return 0;

}