#include "Player.h"
#include "PlayerState.h"
#include <iostream>

GameObject* createPlayer()
{
	GameObject* player = new GameObject({ 200,200 });
	Shape* sprite = new Shape();
	Variables* var = new Variables();
	Collider* collider = new Collider();
	sprite->setRectangle({ 64.f,64.f }, sf::Color::White);
	sprite->setTexture("player.png");
	sprite->setTextureRect({ { 0,0 }, {54, 54} });
	player->AddComponent(sprite);
	player->AddComponent(collider);
	player->AddComponent(var);
	var->addFloat("velocityY", 0.0f);
	var->addFloat("gravity", 0.485f);
	var->addFloat("jumpForce", -11.35f);
	var->addFloat("isGrounded", 0.0f); 
	var->addFloat("isDead", 0.0f);
	return player;

}

void MovePl(GameObject* player, Scene* scene) {

	InputManager::RegisterKeyHold("Space", [player]()
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
						float bw = 60.f;
						float bh = 60.f;

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
							continue; // pas besoin de v�rifier la collision rectangulaire
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
					if (isDead)
					{
						if (!PlayerState::GetInstance().isInvincible)
						{
							if (PlayerState::GetInstance().activePowerup == PowerupType::Invincibility)
							{
								PlayerState::GetInstance().ActivateInvincibility();
								PlayerState::GetInstance().activePowerup = PowerupType::None;
								std::cout << "Invincibilite activee !" << std::endl;
							}
							else
							{
								
								PlayerState::GetInstance().TakeDamage();

								if (PlayerState::GetInstance().IsDead())
								{
									
									var->setFloat("isDead", 1.0f);
								}
								else
								{
									
									PlayerState::GetInstance().ActivateInvincibility();
									std::cout << "HP restants : " << PlayerState::GetInstance().currentHp
										<< "/" << PlayerState::GetInstance().maxHp << std::endl;
								}
							}
						}
					}

					
					if (var->getFloat("isDead") == 0.0f)
					{
						player->getTransform().pos.y = nextY;
						var->setFloat("velocityY", velocityY);
					}

					
					Shape* shape = player->GetComponent<Shape>();
					if (shape != nullptr)
					{
						if (PlayerState::GetInstance().isInvincible)
						{
							float t = PlayerState::GetInstance().invincibilityTimer;
							bool visible = (int)(t * 10) % 2 == 0;
							shape->setVisible(visible);
						}
						else
						{
							shape->setVisible(true);
						}
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
