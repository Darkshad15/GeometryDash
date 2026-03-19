#include "Component.h"


Text::Text():
	text(this->font)
{
	if (!this->font.openFromFile("ProtoNerdFontMono-Regular.ttf"))
	{
		std::cout << "Erreur de chargement de la font par defaut " << std::endl;
	}
	this->font.setSmooth(false);

	txt = "test";
	text.setString("test");
	text.setFont(this->font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);

}

Text::Text(std::string text,int size,sf::Color color,std::string font):
	text(this->font)
{
	if (!this->font.openFromFile(font))
	{
		std::cout << "Erreur de chargement de la font " << font << std::endl;
	}
	this->font.setSmooth(false);

	txt = text;
	this->text.setString(text);
	this->text.setFont(this->font);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
}

void Text::Start()
{

}

void Text::Update()
{

	this->text.setPosition({ owner->getTransform().pos.x,owner->getTransform().pos.y });
}

void Text::Render(sf::RenderWindow& window)
{
	window.draw(text);
}