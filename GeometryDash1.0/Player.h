#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Component.h"
#include "InputManager.h"
#include "Event.h"
#include "Scene.h"  
#include "Elements.h"

GameObject* createPlayer();

void MovePl(GameObject* player, Scene* scene);
void updColision(GameObject* player, Elements* elem);