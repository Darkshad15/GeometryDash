#include "Player.h"
#include <iostream>

GameObject* createPlayer()
{
	GameObject* player = new GameObject({ 200,400 });
	Shape* sprite = new Shape();
	Variables* var = new Variables();
	var->addFloat("speed", 2.0f);
	sprite->setRectangle({64.f,64.f}, sf::Color::Green);
	player->AddComponent(sprite);
	player->AddComponent(var);
	var->addFloat("velocityY", 0.0f);
	var->addFloat("gravity", 0.6f);      
	var->addFloat("jumpForce", -12.0f);   
	var->addFloat("groundY", 400.0f);    // Sol temporaire
	return player;
}

void MovePl(GameObject* player) {

	InputManager::RegisterKeyPress("Space", [player]()
		{
			Variables* var = player->GetComponent<Variables>();
			if (var != nullptr) {
				float groundY = var->getFloat("groundY");

				
				if (player->getTransform().pos.y >= groundY) {
					
					var->setFloat("velocityY", var->getFloat("jumpForce"));
					std::cout << "Le joueur saute" << std::endl;
				}
			}
		});
			{
				
				Event::CreateEvent(-1, [player]()
					{
						if (player != nullptr && player->getActive())
						{
							Variables* var = player->GetComponent<Variables>();
							if (var != nullptr) {
								float velocityY = var->getFloat("velocityY");
								float gravity = var->getFloat("gravity");
								float groundY = var->getFloat("groundY");

				
								velocityY += gravity;

						
								player->getTransform().pos.y += velocityY;

								
								if (player->getTransform().pos.y >= groundY) {
									player->getTransform().pos.y = groundY; 
									velocityY = 0.0f; 
								}

								var->setFloat("velocityY", velocityY);
							}
						}
					});
			}
		
	
}



