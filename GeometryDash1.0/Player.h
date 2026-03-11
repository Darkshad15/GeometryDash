#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Component.h"
#include "InputManager.h"
#include "Event.h"

GameObject* createPlayer();

void MovePl(GameObject* player);