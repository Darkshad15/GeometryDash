#include "Component.h"
Shape::Shape() {
    
}
void Shape::Start() {
    
}

void Shape::Update() {
    float x = owner->getTransform().pos.x;
    float y = owner->getTransform().pos.y;
    if (currentType == Type::RECTANGLE) {
        rectangle.setOrigin({ 32.f, 32.f });
        rectangle.setPosition({ x + 32.f, y + 32.f });
    }
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
    sf::FloatRect bounds = triangle.getLocalBounds();
    triangle.setOrigin({ bounds.size.x / 2.f, 0.f });
}

sf::FloatRect Shape::getBounds() {
    if (currentType == Type::RECTANGLE) return rectangle.getGlobalBounds();
    if (currentType == Type::CIRCLE)    return circle.getGlobalBounds();
    if (currentType == Type::TRIANGLE)  return triangle.getGlobalBounds();
    return sf::FloatRect();
}

void Shape::Render(sf::RenderWindow& window) {
    if (!isVisible) return;
    if (currentType == Type::RECTANGLE) window.draw(rectangle);
    else if (currentType == Type::CIRCLE)    window.draw(circle);
    else if (currentType == Type::TRIANGLE)  window.draw(triangle);
}

void Shape::setTexture(const std::string& path)
{
    texture.loadFromFile(path);  
    if (currentType == Type::RECTANGLE) rectangle.setTexture(&texture);
    if (currentType == Type::CIRCLE)    circle.setTexture(&texture);
    if (currentType == Type::TRIANGLE)  triangle.setTexture(&texture);
}
void Shape::setTextureRect(sf::IntRect rect)
{
    
    if (currentType == Type::RECTANGLE)  rectangle.setTextureRect(rect);;
    if (currentType == Type::CIRCLE)     circle.setTextureRect(rect);;
    if (currentType == Type::TRIANGLE)   triangle.setTextureRect(rect);;
}
void Shape::setVisible(bool Visible) {
    isVisible = Visible;
}

void Shape::setRotation(float angle)
{
    if (currentType == Type::RECTANGLE) rectangle.setRotation(sf::degrees(angle));
    else if (currentType == Type::CIRCLE) circle.setRotation(sf::degrees(angle));
    else if (currentType == Type::TRIANGLE) triangle.setRotation(sf::degrees(angle));
}