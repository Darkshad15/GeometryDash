#include "Elements.h"


Elements::Elements() {

}


void Elements::logic()
{
	if (type == 1) {
		if (gameObject) {
			Collider* col = gameObject->GetComponent<Collider>();
			Shape* rect = gameObject->GetComponent<Shape>();
		}
	}
	else if (type == 2) {

	}
	else if (type == 3) {
		if (gameObject) {
			Collider* col = gameObject->GetComponent<Collider>();
			Shape* rect = gameObject->GetComponent<Shape>();
		}
	}
}

void Elements::draw(sf::RenderWindow& win)
{

}



GameObject* Elements::createBlock()
{
	GameObject* block = new GameObject({ 100,100 });
	Shape* shape = new Shape();
	shape->setRectangle({ 58.f, 58.f }, sf::Color(0, 0, 128));
	Variables* var = new Variables();
	Collider* collision = new Collider();
	var->addInt("Type", 1);
	type = var->getInt("Type");
	block->AddComponent(collision);
	block->AddComponent(shape);
	return block;
}


GameObject* Elements::createCircle()
{
	GameObject* block = new GameObject({ 100,100 });
	Shape* shape = new Shape();
	shape->setCircle({ 20.f }, sf::Color::Cyan);
	Variables* var = new Variables();
	CircleCollider* collision = new CircleCollider(shape->getCircle());
	var->addInt("Type", 3);
	type = var->getInt("Type");
	block->AddComponent(shape);
	block->AddComponent(collision);
	return block;
}

GameObject* Elements::createSpike()
{
	GameObject* block = new GameObject({ 100,100 });
	Shape* shape = new Shape();
	shape->setTriangle(34.f, sf::Color(254, 52, 126));
	Variables* var = new Variables();
	TriangleCollider* collision = new TriangleCollider(shape->getTriangle());
	var->addInt("Type", 2);
	type = var->getInt("Type");
	block->AddComponent(collision);
	block->AddComponent(shape);
	return block;
}






