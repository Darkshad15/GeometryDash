#include "Scenes.h"
#include "SceneModule.h"
#include "Engine.h"
#include "Color.h"
#include "Blink.h"
#include "DelayedMusic.h"
#include "DelayedSkull.h"
#include "Boutton.h"
#include "Settings.h"

#include <SFML/Graphics.hpp>
#include <windows.h>
#undef CreateEvent 
#include <thread>
#include <chrono>



extern unsigned int screenW;
extern unsigned int screenH;

Scenes sc;

void Scenes::CreateButton(Scene* scene, const std::string& texte, const std::string& imagePath,
    float posY, std::function<void(GameObject*)> onClick, float delay, float scale, float posX)
{
    float btnW = 874 * scale;
    float btnH = 320 * scale;
    float btnX = (posX < 0)
        ? (screenW / 2.0f) - (btnW / 2.0f)  // centré par défaut
        : posX - (btnW / 2.0f);              // position custom
    float btnY = posY - (btnH / 2.0f);

    SpriteRenderer* sprite = new SpriteRenderer(imagePath, { 874, 320 }, { 1, 1 });
    sprite->setAnimated(false);
    sprite->setScale(scale);

    GameObject* btn = new GameObject({ btnX, btnY });
    btn->AddComponent(sprite);
    btn->setClickable(true);
    scene->AddGameObject(btn);

    // Texte centré sur le bouton
    sf::Font font(fontPath);
    sf::Text sfText(font, texte, 40);
    auto txtBounds = sfText.getLocalBounds();
    float txtX = (posX < 0)
        ? (screenW / 2.0f) - (txtBounds.size.x / 2.0f) - txtBounds.position.x
        : posX - (txtBounds.size.x / 2.0f) - txtBounds.position.x; // centré sur posX
    float txtY = posY - (txtBounds.size.y / 2.0f) - txtBounds.position.y;

    GameObject* txt = new GameObject({ txtX, txtY });
    txt->AddComponent(new Text(texte, 40, White, fontPath));
    txt->setClickable(true);
    scene->AddGameObject(txt);

    InputManager::RegisterClickableObject(btn, onClick);
    InputManager::RegisterClickableObject(txt, onClick);

    scene->AddOnStartCallback([btn, txt, onClick, btn_sprite = sprite, btnX, btnY, btnH, posX, scale]() {
        InputManager::RegisterClickableObject(btn, onClick);
        InputManager::RegisterClickableObject(txt, onClick);
        InputManager::RegisterHoverObject(btn,
            [btn, btn_sprite, btnX, btnY, btnH, posX](GameObject* obj) {
                float newScale = 0.23f;
                float newW = 874 * newScale;
                float newH = 320 * newScale;
                btn_sprite->setScale(newScale);
                btn->getTransform().pos.x = (posX < 0)
                    ? (screenW / 2.0f) - (newW / 2.0f)
                    : posX - (newW / 2.0f);
                btn->getTransform().pos.y = btnY - ((newH - btnH) / 2.0f);
            },
            [btn, btn_sprite, btnX, btnY, scale](GameObject* obj) {
                btn_sprite->setScale(scale);
                btn->getTransform().pos.x = btnX;
                btn->getTransform().pos.y = btnY;
            }
        );
        });

    if (delay > 0.f) {
        btn->AddComponent(new DelayedButton(delay, txt));
    }
}
void Scenes::Start()
{
    // Callback F11
    Engine::GetInstance()->getSceneModule()->onFullscreenToggle = []() {
        Settings::GetInstance().ToggleFullscreen();
        };

    // Callback après changement de résolution
    Engine::GetInstance()->getSceneModule()->onFullscreenApplied = [this]() {
        std::string sceneName = Engine::GetInstance()->getSceneModule()->GetActiveScene()->getName();

        if (sceneName == "Option") {
            MainData newMain = CreateMain();
            OptionData optionData = CreateOption(newMain);
            Engine::GetInstance()->getSceneModule()->SetPendingScene(optionData.scene);
        }
        else if (sceneName == "MainMenu") {
            MainData newMain = CreateMain();
            Engine::GetInstance()->getSceneModule()->SetPendingScene(newMain.scene);
        }
        else if (sceneName == "Game Over") {
            MainData newMain = CreateMain();
            GameOverData goData = CreateGameover(newMain);
            Engine::GetInstance()->getSceneModule()->SetPendingScene(goData.scene);
        }
        };

    // Lancer le menu principal
    MainData mainData = CreateMain();
    Engine::GetInstance()->getSceneModule()->SetActiveScene(mainData.scene);
}

MainData Scenes::CreateMain()
{
    Scene* mainMenu = new Scene("MainMenu", { screenW, screenH });
    GameOverData goData = CreateGameover({ mainMenu });   

    // Titre
    std::string titreStr = "Gamuo desu !";
    GameObject* title = new GameObject({ CenterX(titreStr, 72, fontPath), 10.0f });
    title->AddComponent(new Text(titreStr, 72, White, fontPath));
    mainMenu->AddGameObject(title);

    InputManager::Initialize(&Engine::GetInstance()->getSceneModule()->getWindow());
    CreateButton(mainMenu, "Jouer", "../Asset/Boutton/red_button.png", CenterY(-75),
        [this](GameObject* obj) {
            LevelData levelData = CreateLevel();
            
            Engine::GetInstance()->getSceneModule()->SetPendingScene(levelData.scene);
        });

    CreateButton(mainMenu, "Option", "../Asset/Boutton/red_button.png", CenterY(+25),
        [this](GameObject* obj) {
            MainData newMain = CreateMain();
            OptionData optionData = CreateOption(newMain);
            Engine::GetInstance()->getSceneModule()->SetPendingScene(optionData.scene);
        });

    CreateButton(mainMenu, "Quitter", "../Asset/Boutton/red_button.png", CenterY(+125), [](GameObject* obj) {
        std::cout << "CLIC QUITTER" << std::endl;
        Engine::GetInstance()->ShutDown();
        });

    return { mainMenu };
}

OptionData Scenes::CreateOption(MainData mainData)
{
    Scene* Option = new Scene("Option", { screenW , screenH });
    std::string titreStr = "Option";
    GameObject* title = new GameObject({ CenterX(titreStr, 75, fontPath), 10.0f });
    title->AddComponent(new Text(titreStr, 72, White, fontPath));
    Option->AddGameObject(title);


    // Bloc "Touche"
    float blocY = CenterY(-180);
    float blocX = CenterX(-300);

    GameObject* touche = new GameObject({ blocX, blocY });
    touche->AddComponent(new Text("Touche", 50, White, fontPath));
    Option->AddGameObject(touche);

    GameObject* config = new GameObject({ blocX, blocY + 60.0f }); // 60px en dessous
    config->AddComponent(new Text("Saut : espace", 25, White, fontPath));
    Option->AddGameObject(config);


    std::string fsStr = Settings::GetInstance().IsFullscreen()
        ? "Plein ecran : ON  (F11)"
        : "Plein ecran : OFF (F11)";

    GameObject* fullscreenInfo = new GameObject({ CenterX(fsStr, 30, fontPath), CenterY(100) });
    fullscreenInfo->AddComponent(new Text(fsStr, 30, White, fontPath));
    Option->AddGameObject(fullscreenInfo);

    float volBlocY = CenterY(0);

    // Texte volume
    int vol = Settings::GetInstance().GetVolume();
    std::string volStr = "Son : " + std::to_string(vol) + "%";

    // Calculer la largeur du texte pour centrer le bloc
    sf::Font font(fontPath);
    sf::Text sfText(font, volStr, 30);
    float txtLargeur = sfText.getLocalBounds().size.x;
    float volBlocX = screenW - 250.0f;
    float centreBlocX = volBlocX + (txtLargeur / 2.0f); // centre du texte

    GameObject* volTxt = new GameObject({ volBlocX, CenterY(-80.0f) });
    volTxt->AddComponent(new Text(volStr, 30, White, fontPath));
    Option->AddGameObject(volTxt);


    // Bouton + aligné sur le centre du texte
    CreateButton(Option, "+", "../Asset/Boutton/red_button.png", CenterY(-20),
        [this](GameObject* obj) {
            Settings::GetInstance().SetVolume(Settings::GetInstance().GetVolume() + 10);
            MainData newMain = CreateMain();
            OptionData optionData = CreateOption(newMain);
            Engine::GetInstance()->getSceneModule()->SetPendingScene(optionData.scene);
        }, 0.f, 0.1f, centreBlocX);



    // Bouton - aligné sur le centre du texte
    CreateButton(Option, "-", "../Asset/Boutton/red_button.png", CenterY(+40),
        [this](GameObject* obj) {
            Settings::GetInstance().SetVolume(Settings::GetInstance().GetVolume() - 10);
            MainData newMain = CreateMain();
            OptionData optionData = CreateOption(newMain);
            Engine::GetInstance()->getSceneModule()->SetPendingScene(optionData.scene);
        }, 0.f, 0.1f, centreBlocX);

    InputManager::Initialize(&Engine::GetInstance()->getSceneModule()->getWindow());
    CreateButton(Option, "Return", "../Asset/Boutton/red_button.png", CenterY(200),
        [this](GameObject* obj) {
            MainData newMain = CreateMain();
            Engine::GetInstance()->getSceneModule()->SetPendingScene(newMain.scene);
        });




    return { Option };
}


LevelData Scenes::CreateLevel()
{
    Scene* mainScene = new Scene("Main", { screenW, screenH });

    Gen* gene = new Gen(mainScene);
    Level* level = gene->getLevel();

    GameObject* player = createPlayer();
    mainScene->AddGameObject(player);
    gene->GenerateLevel();
    gene->DrawAllLevels(mainScene);

    mainScene->AddOnStartCallback([player, mainScene, level]() {
        MovePl(player, mainScene);

        Event::CreateEvent(-2, [level]() {
            static sf::Clock clock;
            float deltaTime = clock.restart().asSeconds();
            level->Move(deltaTime);
            });

        Event::CreateEvent(-3, [level, player]() {
            Variables* var = player->GetComponent<Variables>();
            if (var != nullptr && var->getFloat("isDead") == 1.0f)
            {
                level->Reset();
                player->SetPosition({ 200.f, 200.f });
                var->setFloat("velocityY", 0.0f);
                var->setFloat("isGrounded", 0.0f);
                player->setActive(true);
                var->setFloat("isDead", 0.0f);
            }
            });
        });

    mainScene->Start();
    return { mainScene };
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

GameOverData Scenes::CreateGameover(MainData mainData)
{
    Scene* GameOver = new Scene("Game Over", { screenW, screenH });
    std::string GameOverStr = "Game Over !";

    // Background
    GameObject* background = new GameObject({ 0, 0 });
    SpriteRenderer* bgSprite = new SpriteRenderer(
        "../Asset/GameOver/background.png",
        { 1284, 1074 },
        { 1, 1 }
    );
    sf::Vector2u winSize = Engine::GetInstance()->getSceneModule()->getWindow().getSize();
    float scaleX = winSize.x / 1284.f;
    float scaleY = winSize.y / 1074.f;
    float scale = std::max(scaleY, scaleX);
    bgSprite->setScale(scale);
    bgSprite->setFond(true);
    background->AddComponent(bgSprite);
    GameOver->AddGameObject(background);

    // Titre
    GameObject* title = new GameObject({ CenterX(GameOverStr, 72, fontPath), 80.0f });
    title->AddComponent(new Text(GameOverStr, 72, White, fontPath));
    GameOver->AddGameObject(title);

    // Skull
    GameObject* Skull = new GameObject({ (float)winSize.x / 2.f, (float)winSize.y / 2.f });
    SpriteRenderer* skullSprite = new SpriteRenderer(
        "../Asset/GameOver/skull.png",
        { 1890, 1417 },
        { 1, 1 }
    );
    float skullScale = (winSize.x * 1.5f) / 1890.f;
    skullSprite->setScale(skullScale);

    Skull->AddComponent(skullSprite);
    Skull->AddComponent(new AudioManager("../Asset/GameOver/harold-screamer.mp3"));
    Skull->AddComponent(new DelayedSkull(2.f));
    GameOver->AddGameObject(Skull);


    CreateButton(GameOver, "Rejouer", "../Asset/Boutton/red_button.png", CenterY(50),
        [this](GameObject* obj) {  
            MainData newMain = CreateMain();  
            Engine::GetInstance()->getSceneModule()->SetPendingScene(newMain.scene);
        }, 3.f);

    return { GameOver };
}