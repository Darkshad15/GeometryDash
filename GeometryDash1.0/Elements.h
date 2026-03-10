#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Scene.h"
class Elements
{ 
protected:
	int type; //1 = block, 2 = piege (le toucher = mort), 3 = special (type portail, auto jump etc)	
	GameObject* gameObject = nullptr;
public:
	Elements();
	int getType() const { return type; }
	void logic();
	virtual void draw(sf::RenderWindow& win);
	GameObject* createBlock();
	GameObject* createEmpty();
	GameObject* createCircle();
	GameObject* createSpike();
};
