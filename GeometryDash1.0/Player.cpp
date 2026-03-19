#include "Player.h"
#include <iostream>

GameObject* createPlayer()
{
	GameObject* player = new GameObject({ 200,200 });
	Shape* sprite = new Shape();
	Variables* var = new Variables();
	Collider* collider = new Collider();
	sprite->setRectangle({ 64.f,64.f }, sf::Color(77, 77, 255));
	player->AddComponent(sprite);
	player->AddComponent(collider);
	player->AddComponent(var);
	var->addFloat("velocityY", 0.0f);
	var->addFloat("gravity", 0.485f);
	var->addFloat("jumpForce", -12.0f);
	var->addFloat("groundY", 400.0f);    // Sol temporaire
	var->addFloat("isGrounded", 0.0f); //1.0f au sol , 0.0f en l'air
	var->addFloat("isDead", 0.0f);
	return player;

}

void MovePl(GameObject* player, Scene* scene) {

	InputManager::RegisterKeyPress("Space", [player]()
		{
			Variables* var = player->GetComponent<Variables>();
			if (var != nullptr && var->getFloat("isGrounded") == 1.0f) {
				var->setFloat("velocityY", var->getFloat("jumpForce"));
				var->setFloat("isGrounded", 0.0f);
				std::cout << "Le joueur saute" << std::endl;
			}
		});

	Event::CreateEvent(-1, [player, scene]()
		{
			if (player != nullptr && player->getActive())
			{
				Variables* var = player->GetComponent<Variables>();

				if (var != nullptr) {
					float velocityY = var->getFloat("velocityY");
					float gravity = var->getFloat("gravity");

					velocityY += gravity;
					float nextY = player->getTransform().pos.y + velocityY;

					// Dimensions du joueur
					float px = player->getTransform().pos.x;
					float py = player->getTransform().pos.y;
					float pw = 64.f;
					float ph = 64.f;

					bool touchGround = false;
					bool isDead = false; // On ajoute un marqueur de mort

					for (GameObject* obj : scene->getLstObj()) {
						if (obj == player || !obj->getActive()) continue;

						float bx = obj->getTransform().pos.x;
						float by = obj->getTransform().pos.y;
						float bw = 64.f;
						float bh = 64.f;

						// === SPIKE : triangle ===
						TriangleCollider* tc = obj->GetComponent<TriangleCollider>();
						if (tc != nullptr) {
							// Tester les 4 coins du joueur contre le triangle
							bool hit = tc->containsPoint({ px,      py })
								|| tc->containsPoint({ px + pw,  py })
								|| tc->containsPoint({ px,      py + ph })
								|| tc->containsPoint({ px + pw,  py + ph });
							if (hit) {
								isDead = true;
							}
							continue; // pas besoin de vérifier la collision rectangulaire
						}


						// === ORBE DE SAUT : cercle ===
						CircleCollider* cc = obj->GetComponent<CircleCollider>();
						if (cc != nullptr) {

							if (cc->DoesCollide(player)) {

								touchGround = true;
							}

							continue;
						}

						// === BLOC NORMAL : rectangle ===
						if (obj->GetComponent<Collider>() == nullptr) continue;

						bool overlapX = (px + pw > bx + 5.f && px < bx + bw - 5.f);
						if (overlapX) {
							if (velocityY > 0.0f && py + ph <= by + 15.f && nextY + ph >= by) {
								nextY = by - ph;
								velocityY = 0.0f;
								touchGround = true;
							}
							else if (nextY + ph > by + 5.f && nextY < by + bh - 5.f) {
								isDead = true;
							}
							if (nextY > 610.f) {
								isDead = true;
							}
						}

					}

					// Game over
					
					if (isDead) {
						std::cout << "Mur ou pic percuté ! Mort du joueur." << std::endl;

						// On déclenche l'Event 1 qui gère le nettoyage et le restart dans Main.cpp
						//Event::SetEventTrue(-3);
						var->setFloat("isDead", 1.0f);
		
					}
					else {
						// On applique la nouvelle position UNIQUEMENT si le joueur est en vie
						player->getTransform().pos.y = nextY;
						var->setFloat("velocityY", velocityY);
					}
				
					
					

					if (touchGround) {
						var->setFloat("isGrounded", 1.0f);
					}
					else {
						var->setFloat("isGrounded", 0.0f);
					}
				}
			}
		});
}
