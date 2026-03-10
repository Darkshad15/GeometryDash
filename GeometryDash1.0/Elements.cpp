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
	else if (type == 3){

	}
}

void Elements::draw(sf::RenderWindow& win)
{

}



GameObject* Elements::createBlock()
{
	GameObject* block = new GameObject({100,100});
	Shape* shape = new Shape();
	shape->setRectangle({ 64.f, 64.f }, sf::Color::Green);
	Variables* var = new Variables();
	Collider* collision = new Collider();
	var->addInt("Type", 1);
	type = var->getInt("Type");
	block->AddComponent(collision);
	block->AddComponent(shape);
	return block;
}
