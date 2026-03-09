#include "Component.h"
#include "Scene.h"




Player::Player(float speed)
{
	direction = Direction::Down;
	s = speed;
}

void Player::Start()
{

}

void Player::Update()
{
	SpriteRenderer* sr = owner->GetComponent<SpriteRenderer>();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		owner->getTransform().pos.y -= s;
		sr->setDirection(Direction::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		owner->getTransform().pos.y += s;
		sr->setDirection(Direction::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		owner->getTransform().pos.x -= s;
		sr->setDirection(Direction::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		owner->getTransform().pos.x += s;
		sr->setDirection(Direction::Right);
	}
}


void Player::Render(sf::RenderWindow& window)
{

}