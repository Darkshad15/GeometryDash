#include "SceneMain.h"

void SceneMain::start(){
	Scene* mainMenu = new Scene("MainMenu", { 800, 600 });

	// Titre
	GameObject* title = new GameObject({ 300, 100 });
	title->AddComponent(new Text("MON JEU", 72));
	mainMenu->AddGameObject(title);

	// Bouton Play
	GameObject* btnPlay = new GameObject({ 350, 300 });
	btnPlay->AddComponent(new Text("Jouer", 48));
	btnPlay->setClickable(true);
	mainMenu->AddGameObject(btnPlay);

}
