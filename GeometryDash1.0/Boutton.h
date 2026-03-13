#pragma once
#include "Component.h"
#include "GameObject.h"

class DelayedButton : public Component
{
private:
    float delay;
    bool appeared = false;
    sf::Clock clock;
    GameObject* txtObj = nullptr;
    sf::Vector2f originalTxtPos;  

public:
    DelayedButton(float delaySeconds, GameObject* txt = nullptr)
        : delay(delaySeconds), txtObj(txt) {
    }

    void Start() override {
        clock.restart();
        owner->setClickable(false);
        SpriteRenderer* sr = owner->GetComponent<SpriteRenderer>();
        if (sr != nullptr)
            sr->setVisible(false);
        if (txtObj != nullptr) {
            txtObj->setClickable(false);
            originalTxtPos = txtObj->getTransform().pos;  
            txtObj->getTransform().pos = { -9999.f, -9999.f };  
        }
    }

    void Update() override {
        if (!appeared && clock.getElapsedTime().asSeconds() >= delay) {
            owner->setClickable(true);
            std::cout << "clickable: " << owner->getClickable() << std::endl;
            std::cout << "pos: " << owner->getTransform().pos.x << ", " << owner->getTransform().pos.y << std::endl;

            SpriteRenderer* sr = owner->GetComponent<SpriteRenderer>();
            if (sr != nullptr) {
                sr->setVisible(true);
                sf::FloatRect b = sr->getSprite().getGlobalBounds();
                std::cout << "bounds: " << b.position.x << "," << b.position.y << " size: " << b.size.x << "," << b.size.y << std::endl;
            }
            if (txtObj != nullptr) {
                txtObj->setClickable(true);
                txtObj->getTransform().pos = originalTxtPos;
            }
            appeared = true;
        }
    }

    void Render(sf::RenderWindow& window) override {}
};