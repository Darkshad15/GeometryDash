#include "Player.h"
#include <iostream>

GameObject* createPlayer()
{
    GameObject* player = new GameObject({ 200, 400 });
    Shape* sprite = new Shape();
    Variables* var = new Variables();
    Collider* col = new Collider(); 

    sprite->setRectangle({ 64.f, 64.f }, sf::Color::Green);
    var->addFloat("speed", 2.0f);
    var->addFloat("velocityY", 0.0f);
    var->addFloat("gravity", 980.f);
    var->addFloat("jumpForce", -500.f);
    var->addBool("grounded", false);
    NewClock* clk = new NewClock();
    
    player->AddComponent(clk);
    player->AddComponent(sprite);
    player->AddComponent(col);
    player->AddComponent(var);
    return player;
}

void MovePl(GameObject* player, Scene* scene)
{
    // Saut
    InputManager::RegisterKeyPress("Space", [player]()
        {
            Variables* var = player->GetComponent<Variables>();
            if (var != nullptr) {
                var->setFloat("velocityY", var->getFloat("jumpForce"));
                std::cout << "Le joueur saute" << std::endl;
            }
        });

    Event::CreateEvent(-2, [player, scene]()
        {
            if (player == nullptr || !player->getActive() || player->GetComponent<Variables>()->getBool("grounded")) return;

            Variables* var = player->GetComponent<Variables>();
            NewClock* clk = player->GetComponent<NewClock>();
            if (var == nullptr || clk == nullptr) return;

            float deltaTime = clk->GetTimeSinceStart();
            clk->RestartClock(); 
            
            deltaTime = std::min(deltaTime, 0.05f);

            float velocityY = var->getFloat("velocityY");
            float gravity = var->getFloat("gravity");

            velocityY += gravity * deltaTime;
            player->getTransform().pos.y += velocityY * deltaTime;

            var->setFloat("velocityY", velocityY);
        });
    
}
void updColision(GameObject* player, Elements* elem)
{
    Event::CreateEvent(-3, [player, elem] {
        
        Collider* playerCol = player->GetComponent<Collider>();
        Collider* blockCol = elem->createBlock()->GetComponent<Collider>();

        if (playerCol->DoesCollide(elem->createBlock())) {
            player->GetComponent<Variables>()->addBool("grounded", true);
        }
        
        
        });
}
