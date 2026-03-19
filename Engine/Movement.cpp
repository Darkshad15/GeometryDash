#include "Component.h"



void Movement::Start() {

}

void Movement::Render(sf::RenderWindow& window) {
    if (!owner) {
        std::cout << "[ERROR] Movement::Render - owner est null!" << std::endl;
        return;
    }

    if (owner->getTransform().pos.x < 0 ||
        owner->getTransform().pos.x > window.getSize().x + 100 ||
        owner->getTransform().pos.y > window.getSize().y + 100)
    {
        if (owner->GetComponent<Variables>()->getInt("Type") == 3) {
            owner->Destroy();
        }
        else {
            owner->SetPosition({ owner->getTransform().pos.x, -70 });
        }
    }
}

void Movement::Update() {
    if (!owner) {
        std::cout << "[ERROR] Movement::Update - owner est null!" << std::endl;
        return;
    }
    owner->getTransform().pos.y += speed;
}