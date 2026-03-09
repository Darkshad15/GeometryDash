#pragma once
#include "Engine.h"

constexpr sf::Color color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
{
	return sf::Color(r, g, b, a);
}

constexpr sf::Color White = color(255, 255, 255);
constexpr sf::Color Red = color(255, 0, 0);
constexpr sf::Color Green = color(0, 255, 0);
