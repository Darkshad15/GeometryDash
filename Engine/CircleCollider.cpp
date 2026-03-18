#include "Component.h"
#include <cmath>

float CircleCollider::getRadius()
{
	if (shape != nullptr) {
		return shape->getRadius();
	}
	return 0.f;
}

sf::Vector2f CircleCollider::getCenter()
{
	if (owner != nullptr && shape != nullptr) {
		float r = getRadius();
		return sf::Vector2f(owner->getTransform().pos.x + r, owner->getTransform().pos.y + r);
	}
	return sf::Vector2f(0.f, 0.f);
}

bool CircleCollider::DoesCollide(GameObject* other)
{
	if (!canCollide || other == nullptr || other == owner)
		return false;

	sf::Vector2f circleCenter = getCenter();
	float circleRadius = getRadius();


	Shape* otherShape = other->GetComponent<Shape>();

	if (otherShape != nullptr) {
		sf::FloatRect rectBounds = otherShape->getBounds();

		float closestX = std::max(rectBounds.position.x, std::min(circleCenter.x, rectBounds.position.x + rectBounds.size.x));
		float closestY = std::max(rectBounds.position.y, std::min(circleCenter.y, rectBounds.position.y + rectBounds.size.y));


		float distanceX = circleCenter.x - closestX;
		float distanceY = circleCenter.y - closestY;


		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		return distanceSquared < (circleRadius * circleRadius);
	}

	return false;
}