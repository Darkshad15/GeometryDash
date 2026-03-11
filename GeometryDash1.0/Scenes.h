#pragma once
#include "Scene.h"
#include <iostream>
#include<vector>


extern unsigned int screenW;
extern unsigned int screenH;


class Scenes
{

private:
	std::string fontPath = "../x64/Font/Berosong-Regular.ttf";

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

	Scene* CreateMain();
	Scene* CreateLevel();
	Scene* CreatePause();
	Scene* CreateGameover();
	

};

