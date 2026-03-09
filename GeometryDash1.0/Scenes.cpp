#include "Scenes.h"
#include "SceneModule.h"
#include "Engine.h"
#include "Color.h"
#include <SFML/Graphics.hpp>
#include <windows.h>


Scene* Scenes::CreateMain()
{
	Scene* mainMenu = new Scene("MainMenu", { 800, 600 });

	// Titre
	GameObject* title = new GameObject({ 300, 100 });
	title->AddComponent(new Text("Gamuo desu !", 72, White, "../x64/Font/arial.ttf"));
	mainMenu->AddGameObject(title);

	// Bouton Play
	GameObject* btnPlay = new GameObject({ 350, 300 });
	btnPlay->AddComponent(new Text("Jouer", 48, Green,"../x64/Font/arial.ttf"));
	btnPlay->setClickable(true);
	mainMenu->AddGameObject(btnPlay);

	return mainMenu;
}


Scene* Scenes::CreatePause()
{
	Scene* Pause = new Scene("MainMenu", { 800, 600 });
	// Titre
	GameObject* title = new GameObject({ 300, 100 });
	title->AddComponent(new Text("Pause", 72, White, "../x64/Font/arial.ttf"));
	Pause->AddGameObject(title);


	return Pause;

}

