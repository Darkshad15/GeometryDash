#include "Component.h"

Projectile::Projectile(float speed, Direction d, GameObject* shootOwner)
{
	this->speed = speed;
	direction = d;
	this->shootOwner = shootOwner;
}

Projectile::Projectile(sf::Vector2f target, float speed,sf::Vector2f start, GameObject* shootOwner)
{
	this->speed = speed;
	this->shootOwner = shootOwner;
	sf::Vector2f dir = target - start;
	float length = std::sqrt(dir.x+32 * dir.x+32 + dir.y * dir.y);
	if (length != 0)
		directionVector = dir / length;
	else
		directionVector = sf::Vector2f(0, 0);
}



void Projectile::Start()
{

}

void Projectile::Update()
{
	SpriteRenderer* sr = owner->GetComponent<SpriteRenderer>();
	if (direction == Direction::Up)
	{
		owner->getTransform().pos.y -= speed;
	}
	if (direction == Direction::Down)
	{
		owner->getTransform().pos.y += speed;
	}
	if (direction == Direction::Left)
	{
		owner->getTransform().pos.x -= speed;
	}
	if (direction == Direction::Right)
	{
		owner->getTransform().pos.x += speed;
	}
	if (direction == Direction::Focus)
	{
		owner->getTransform().pos += directionVector * speed;
	}
	
}




void Projectile::Render(sf::RenderWindow& window)
{
	if (owner->getTransform().pos.x < 0 || owner->getTransform().pos.y <0 || owner->getTransform().pos.x > window.getSize().x || owner->getTransform().pos.y > window.getSize().y)
	{
		owner->Destroy();
	}
}