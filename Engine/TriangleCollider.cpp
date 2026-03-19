#include "Component.h"

std::array<sf::Vector2f, 3> TriangleCollider::getVertices()
{
    return {
            shape->getTransform().transformPoint(shape->getPoint(0)),
            shape->getTransform().transformPoint(shape->getPoint(1)),
            shape->getTransform().transformPoint(shape->getPoint(2))
    };
}

bool TriangleCollider::pointInTriangle(sf::Vector2f P, sf::Vector2f A, sf::Vector2f B, sf::Vector2f C)
{
    auto sign = [](sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        };

    float d1 = sign(P, A, B);
    float d2 = sign(P, B, C);
    float d3 = sign(P, C, A);

    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(hasNeg && hasPos);
}

bool TriangleCollider::containsPoint(sf::Vector2f P)
{
    auto [A, B, C] = getVertices();
    return pointInTriangle(P, A, B, C);
}

bool TriangleCollider::DoesCollide(GameObject* other) {
    sf::Vector2f otherPos = {
        other->getTransform().pos.x,
        other->getTransform().pos.y
    };
    return containsPoint(otherPos);
}