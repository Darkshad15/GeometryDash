#include "Component.h"

void Collider::Start()
{
	
}

void Collider::Update()
{
	
}


void Collider::Render(sf::RenderWindow& window)
{
	
}

bool Collider::DoesCollide(GameObject* target)
{
	sf::FloatRect objBounds = owner->GetComponent<SpriteRenderer>()->getBounds();
	sf::FloatRect targetBounds = target->GetComponent<SpriteRenderer>()->getBounds();
	if (objBounds.findIntersection(targetBounds))
		return true;
	else
		return false;
}