#pragma once
#include "Component.h"
#include "GameObject.h"

class Blink : public Component
{
private:
	float interval = 0.6f;  // clignote toutes les 0.5 secondes
	NewClock* clock;

public:

	void Start() override {
		clock = owner->GetComponent<NewClock>();
		clock->StartClock();
	}

	void Update() override {
		if (clock->GetTimeSinceStart() >= interval) {
			SpriteRenderer* sr = owner->GetComponent<SpriteRenderer>();
			sr->setVisible(!sr->getVisible());  // inverse visible/invisible
			clock->ResetClock();
			clock->StartClock();
		}
	}

	void Render(sf::RenderWindow& window) override {
		// rien à dessiner ici
	}

};
