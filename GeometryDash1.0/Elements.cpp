#include "Elements.h"


Elements::Elements(int t) {
	type = t;
}


void Elements::logic()
{
	if (type == 1) {

	}
	else if (type == 2) {

	}
	else if (type == 3) {

	}
}

void Elements::draw(sf::RenderWindow& win)
{

}

Block::Block() : Elements(1) {
	rectangle.setSize({ 64.f,64.f });
	rectangle.setFillColor(sf::Color(150, 50, 250));
}

void Block::draw(sf::RenderWindow& win)
{
	win.draw(rectangle);
}
