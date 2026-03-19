#pragma once
#include "SFML/Graphics.hpp"

class Transform
{
public:
	sf::Vector2f pos;
	float rotation = 0.f;

	float scale_x = 1.f;
	float scale_y = 1.f;

	float width;
	float height;
};

