#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
int main()
{
    Engine engine({ 800, 600 }, "Mon Premier Jeu");

    Scene* mainScene = new Scene("Main", { 800, 600 });

    GameObject* player = new GameObject({ 400, 300 });
    SpriteRenderer* sprite = new SpriteRenderer(
        "player.png",    // Fichier image
        { 64, 64 },        // Taille du sprite
        { 1, 1 }           // Grille d'animation
    );

    player->AddComponent(sprite);

    mainScene->AddGameObject(player);

    // 5. Activer la scène et démarrer
    engine.getSceneModule()->SetActiveScene(mainScene);
    mainScene->Start();
    engine.Start();

    return 0;

}