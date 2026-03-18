#pragma once
#include "Scene.h"
#include <iostream>
#include<vector>
#include "Gen.h"
#include "Level.h"
#include "Player.h"
#include "Elements.h"


extern unsigned int screenW;
extern unsigned int screenH;


struct GameOverData {
	Scene* scene;
};

struct LevelData {
	Scene* scene;
};

struct OptionData {
	Scene* scene;
};

struct MainData {
	Scene* scene;
};

class Scenes
{

private:
	std::string fontPath = "../Asset/Font/Moonstrike.otf";

	float CenterX(float offsetX = 0.0f) {
		return (screenW / 2.0f) + offsetX;
	}

	float CenterX(const std::string& texte, float taillePolice, const std::string& cheminPolice) {
		sf::Font font(cheminPolice);  
		sf::Text sfText(font, texte, (unsigned int)taillePolice);  

		float largeur = sfText.getLocalBounds().size.x;  
		return (screenW / 2.0f) - (largeur / 2.0f);
	};
	float CenterY(float offsetY = 0) {
		return (screenH / 2.0f) + offsetY;
	}

public:

	void Start();

	void CreateButton(Scene* scene, const std::string& texte, const std::string& imagePath,
		float posY, std::function<void(GameObject*)> onClick,
		float delay = 0.f, float scale = 0.2f, float posX = -1.0f);

	MainData CreateMain();

	OptionData CreateOption(MainData mainData);

	LevelData CreateLevel();

	Scene* CreatePause();

	GameOverData CreateGameover(MainData mainData);

};

