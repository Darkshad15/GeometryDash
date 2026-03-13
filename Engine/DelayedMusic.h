#pragma once
#include "Component.h"

class DelayedMusic : public Component
{
private:
    float delay;
    float elapsed = 0.f;
    bool played = false;
    NewClock* clock = nullptr;

public:
    DelayedMusic(float delaySeconds) : delay(delaySeconds) {}

    void Start() override {
        clock = owner->GetComponent<NewClock>();
        clock->StartClock();
    }

    void Update() override {
        if (!played && clock->GetTimeSinceStart() >= delay) {
            owner->GetComponent<AudioManager>()->Play();
            played = true;
        }
    }

    void Render(sf::RenderWindow& window) override {}
};