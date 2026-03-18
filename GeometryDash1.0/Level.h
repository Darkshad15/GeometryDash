#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Elements.h"
class Level
{
private:
	int difficulty;
	int order;
	enum class Bloc {
		VIDE = 0,
		MUR = 1,
		SIKE = 2,
		ENNEMI = 3
	};
	Elements* elem;
	std::vector<std::vector<int>> LevelParts;
	std::vector<GameObject*> spawnedObjects;
	std::vector<sf::Vector2f> startPositions;
public:
	Level(int diff, int ord);
	~Level();
	void Draw(Scene* scene, std::vector<std::vector<int>> part, float offsetX);
	void Move(float deltaTime);
	std::vector<std::vector<int>> Load(const std::string& chemin);
	void Reset();
};