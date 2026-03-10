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
		SPAWN = 2,
		ENNEMI = 3
	};
	Elements* elem;
	std::vector<std::vector<int>> LevelParts;
	std::vector<GameObject*> spawnedObjects;
public:
	Level(int diff, int ord);
	~Level();
	void Draw(Scene* scene);
	std::vector<std::vector<int>> Load(const std::string& chemin);
};

