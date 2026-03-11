#include "Scenes.h"
#include "SceneModule.h"
#include "Engine.h"
#include "Color.h"
#include <SFML/Graphics.hpp>
#include <windows.h>

extern unsigned int screenW;
extern unsigned int screenH;

Scenes sc;

void Scenes::Start()
{
	Engine::GetInstance()->getSceneModule()->SetActiveScene(CreateMain());

}


Scene* Scenes::CreateMain()
{
    Scene* mainMenu = new Scene("MainMenu", { screenW, screenH });
   

    // Titre centré
    std::string titreStr = "Gamuo desu !";
    GameObject* title = new GameObject({ CenterX(titreStr, 72, fontPath), 80.0f });
    title->AddComponent(new Text(titreStr, 72, White, fontPath));
    mainMenu->AddGameObject(title);

    // Bouton Play centré
    std::string playStr = "Jouer";
    GameObject* btnPlay = new GameObject({ CenterX(playStr, 48, fontPath), CenterY(-50) });
    btnPlay->AddComponent(new Text(playStr, 48, Green, fontPath));
    btnPlay->setClickable(true);
    mainMenu->AddGameObject(btnPlay);

    InputManager::Initialize(&Engine::GetInstance()->getSceneModule()->getWindow());
    InputManager::RegisterClickableObject(btnPlay, [this](GameObject* obj) {
        Engine::GetInstance()->getSceneModule()->SetActiveScene(CreateGameover());
        });

    std::string quitStr = "Quitter";
    GameObject* btnQuitter = new GameObject({ CenterX(quitStr, 10, fontPath), CenterY(-70) });
    btnQuitter->AddComponent(new Text(quitStr, 10, Red, fontPath));
    btnQuitter->setClickable(true);
    mainMenu->AddGameObject(btnQuitter);

    InputManager::Initialize(&Engine::GetInstance()->getSceneModule()->getWindow());
    InputManager::RegisterClickableObject(btnQuitter, [this](GameObject* obj)
        {
            Engine::GetInstance()->ShutDown();
        });


    return mainMenu;
}


Scene* Scenes::CreatePause()
{
	Scene* Pause = new Scene("MainMenu", { screenW, screenH });

    std::string pauseStr = "Pause";
	// Titre
	GameObject* title = new GameObject({ CenterX(pauseStr, 72, fontPath), 80.0f });
	title->AddComponent(new Text(pauseStr, 72, White, fontPath));
	Pause->AddGameObject(title);


	return Pause;

}

Scene* Scenes::CreateGameover()
{
	Scene* GameOver = new Scene("Game Over" ,{800, 600});

    std::string GameOverStr = "Game Over !";

	GameObject* title = new GameObject({ CenterX(GameOverStr, 72, fontPath), 80.0f });
	title->AddComponent(new Text(GameOverStr, 72, White, fontPath));
	GameOver->AddGameObject(title);

	return GameOver;
}

