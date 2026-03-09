#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Scene.h"
class Elements
{ 
protected:
	int type; //1 = block, 2 = piege (le toucher = mort), 3 = special (type portail, auto jump etc)
public:
	Elements(int t);
	int getType() const { return type; }
	void logic();
	virtual void draw(sf::RenderWindow& win);
};

class Block : public Elements
{
private:
	float height = 64.f;
	float widht = 64.f;
	sf::RectangleShape rectangle;

public:
	Block();
	void draw(sf::RenderWindow& win) override;
};
