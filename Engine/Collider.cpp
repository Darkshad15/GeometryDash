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
	sf::FloatRect objBounds;
	if (owner->GetComponent<SpriteRenderer>()) {
		objBounds = owner->GetComponent<SpriteRenderer>()->getBounds();
	}
	else if (owner->GetComponent<Shape>()) {
		objBounds = owner->GetComponent<Shape>()->getBounds();
	}



	sf::FloatRect targetBounds;
	if (target->GetComponent<SpriteRenderer>()) {
		targetBounds = target->GetComponent<SpriteRenderer>()->getBounds();
	}
	else if (target->GetComponent<Shape>()) {
		targetBounds = target->GetComponent<Shape>()->getBounds();	
	}

	if (objBounds.findIntersection(targetBounds))
		return true;
	else
		return false;
}