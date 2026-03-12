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
    float btnW = 874 * scale;  
    float btnH = 320 * scale;  
    float btnX = (screenW / 2.0f) - (btnW / 2.0f);  // 312.6
    float btnY = posY - (btnH / 2.0f);

    SpriteRenderer* sprite = new SpriteRenderer(imagePath, { 874, 320 }, { 1, 1 });  
    sprite->setAnimated(false);
    sprite->setScale(scale);

    GameObject* btn = new GameObject({ btnX, btnY });
    btn->AddComponent(sprite);
    btn->setClickable(true);
    scene->AddGameObject(btn);

    // Texte centré
    sf::Font font(fontPath);
    sf::Text sfText(font, texte, 40);
    auto txtBounds = sfText.getLocalBounds();
    float txtX = (screenW / 2.0f) - (txtBounds.size.x / 2.0f) - txtBounds.position.x;
    float txtY = posY - (txtBounds.size.y / 2.0f) - txtBounds.position.y;

    GameObject* txt = new GameObject({ txtX, txtY });
    txt->AddComponent(new Text(texte, 40, White, fontPath));
    txt->setClickable(true);
    scene->AddGameObject(txt);

    InputManager::RegisterClickableObject(btn, onClick);
    InputManager::RegisterClickableObject(txt, onClick);

    InputManager::RegisterHoverObject(btn,
        [btn, sprite, btnX, btnY, btnH](GameObject* obj) {
            float newScale = 0.23f;
            float newW = 874 * newScale;
            float newH = 320 * newScale;
            sprite->setScale(newScale);
            btn->getTransform().pos.x = (screenW / 2.0f) - (newW / 2.0f);  // recentre X
            btn->getTransform().pos.y = btnY - ((newH - btnH) / 2.0f);      // recentre Y
        },
        [btn, sprite, btnX, btnY](GameObject* obj) {
            sprite->setScale(0.2f);
            btn->getTransform().pos.x = btnX;  // remet position originale
            btn->getTransform().pos.y = btnY;
        }
    );
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
        InputManager::Clear();
        });

    CreateButton(mainMenu, "Quitter", "../Asset/Boutton/red_button.png", CenterY(+50), [](GameObject* obj) {
        std::cout << "CLIC QUITTER" << std::endl;
        Engine::GetInstance()->ShutDown();
        InputManager::Clear();
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
    Scene* GameOver = new Scene("Game Over", { screenW, screenH });
    std::string GameOverStr = "Game Over !";

    GameObject* background = new GameObject({ 0, 0 });
    SpriteRenderer* bgSprite = new SpriteRenderer(
        "../Asset/GameOver/background.png",
        { 1284 , 1074},
        { 1, 1 }
    );

    sf::Vector2u winSize = Engine::GetInstance()->getSceneModule()->getWindow().getSize();
    float scaleX = winSize.x / 1890.f;
    float scaleY = winSize.y / 1417.f;
    float scale = std::max(scaleX, scaleY);

    bgSprite->setScale(scale);
    bgSprite->setFond(true);    
    background->AddComponent(bgSprite);
    GameOver->AddGameObject(background);
    background->Start();


    // Titre
    GameObject* title = new GameObject({ CenterX(GameOverStr, 72, fontPath), 80.0f });
    title->AddComponent(new Text(GameOverStr, 72, White, fontPath));
    GameOver->AddGameObject(title);
    title->Start();

    return GameOver;
}