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
    GameObject* background = new GameObject({ 0, -45 });
    SpriteRenderer* bg = new SpriteRenderer(
        "Assets/image2.png",
        { 3200, 1800 },
        { 0, 0 }
    );
    //bg->setFond(true);
    bg->setScale(0.46875f);
    background->AddComponent(bg);
    GameObject* player;
    player = createPlayer();
    MovePl(player, mainScene);
    
    mainScene->AddGameObject(background);
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

    Event::CreateEvent(-3, [&level, &player]() {
        Variables* var = player->GetComponent<Variables>();
        if (var != nullptr && var->getFloat("isDead") == 1.0f)
        {
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
            var->setFloat("isDead", 0.0f);
        }

        });


    engine.Start();

    return 0;

}