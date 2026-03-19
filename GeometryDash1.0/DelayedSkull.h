#pragma once
#include "Component.h"
#include "GameObject.h"

class DelayedSkull : public Component
{
private:
    float delay;
    bool appeared = false;
    sf::Clock clock;

public:
    DelayedSkull(float delaySeconds) : delay(delaySeconds) {}

    void Start() override {
        clock.restart();
        owner->GetComponent<SpriteRenderer>()->setCenterOrigin();  
        owner->GetComponent<SpriteRenderer>()->setVisible(false);
    }
    void Update() override {
        if (!appeared && clock.getElapsedTime().asSeconds() >= delay) {
            owner->GetComponent<SpriteRenderer>()->setVisible(true);
            owner->GetComponent<AudioManager>()->Play();
            appeared = true;
        }
    }

    void Render(sf::RenderWindow& window) override {}
};