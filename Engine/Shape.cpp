#include "Component.h"
Shape::Shape() {
    
}
void Shape::Start() {
    
}

void Shape::Update() {
    float x = owner->getTransform().pos.x;
    float y = owner->getTransform().pos.y;
    if (currentType == Type::RECTANGLE) rectangle.setPosition({x,y});
    else if (currentType == Type::CIRCLE) circle.setPosition({ x,y });
    else if (currentType == Type::TRIANGLE) triangle.setPosition({ x,y });
}


void Shape::setRectangle(sf::Vector2f s, sf::Color c) {
    currentType = Type::RECTANGLE;
    rectangle.setSize(s);
    rectangle.setFillColor(c);
}

void Shape::setCircle(float radius, sf::Color c) {
    currentType = Type::CIRCLE;
    circle.setRadius(radius);
    circle.setFillColor(c);
}

void Shape::setTriangle(float radius, sf::Color c) {
    currentType = Type::TRIANGLE;
    triangle.setPointCount(3); 
    triangle.setRadius(radius);
    triangle.setFillColor(c);
}

sf::FloatRect Shape::getBounds() {
    if (currentType == Type::RECTANGLE) return rectangle.getGlobalBounds();
    if (currentType == Type::CIRCLE)    return circle.getGlobalBounds();
    if (currentType == Type::TRIANGLE)  return triangle.getGlobalBounds();
    return sf::FloatRect();
}

void Shape::Render(sf::RenderWindow& window) {
    if (currentType == Type::RECTANGLE) window.draw(rectangle);
    else if (currentType == Type::CIRCLE)    window.draw(circle);
    else if (currentType == Type::TRIANGLE)  window.draw(triangle);
}