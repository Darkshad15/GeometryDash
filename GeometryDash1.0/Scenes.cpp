#include "Scenes.h"
#include "SceneModule.h"
#include "Engine.h"
#include "Color.h"
#include <SFML/Graphics.hpp>
#include <windows.h>

extern unsigned int screenW;
extern unsigned int screenH;

Scenes sc;

void Scenes::CreateButton(Scene* scene, const std::string& texte, const std::string& imagePath,
    float posY, std::function<void(GameObject*)> onClick)
    {
        float scale = 0.2f;
        float btnW = 874 * scale;   // largeur réelle affichée
        float btnH = 320 * scale;   // hauteur réelle affichée

        float btnX = (screenW / 2.0f) - (btnW / 2.0f);  // coin gauche du sprite
        float btnY = posY - (btnH / 2.0f);               // coin haut du sprite

        // Sprite
        SpriteRenderer* sprite = new SpriteRenderer(imagePath, { 974, 320 }, { 1, 1 });
        sprite->setAnimated(false);
        sprite->setScale(scale);

        GameObject* btn = new GameObject({ btnX, btnY });
        btn->AddComponent(sprite);
        btn->setClickable(true);
        scene->AddGameObject(btn);

        float txtX = CenterX(texte, 40, fontPath);
        float txtY = btnY + (btnH / 2.0f)- 30.f;

        GameObject* txt = new GameObject({ txtX, txtY });
        txt->AddComponent(new Text(texte, 40, White, fontPath));
        scene->AddGameObject(txt);

        InputManager::RegisterClickableObject(btn, onClick);

    }

void Scenes::Start()
{
	Engine::GetInstance()->getSceneModule()->SetActiveScene(CreateMain());

}


Scene* Scenes::CreateMain()
{
    Scene* mainMenu = new Scene("MainMenu", { screenW, screenH });
    Scene* gameOver = CreateGameover();  // créée à l'avance

    // Titre
    std::string titreStr = "Gamuo desu !";
    GameObject* title = new GameObject({ CenterX(titreStr, 72, fontPath), 80.0f });
    title->AddComponent(new Text(titreStr, 72, White, fontPath));
    mainMenu->AddGameObject(title);

    InputManager::Initialize(&Engine::GetInstance()->getSceneModule()->getWindow());

    // Boutons
    CreateButton(mainMenu, "Jouer", "../Asset/Boutton/red_button.png", CenterY(-50), [gameOver](GameObject* obj) {
        std::cout << "CLIC JOUER" << std::endl;
        Engine::GetInstance()->getSceneModule()->SetActiveScene(gameOver);  
        });

    CreateButton(mainMenu, "Quitter", "../Asset/Boutton/red_button.png", CenterY(+50), [](GameObject* obj) {
        std::cout << "CLIC QUITTER" << std::endl;
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

