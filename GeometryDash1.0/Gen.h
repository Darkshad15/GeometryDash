#pragma once
#include "Level.h"
#include <iostream>
#include <string>
#include <vector>
#include "Scene.h"
#include <cstdlib>
#include <ctime>
class Gen
{
private:
	Level* lvl;
	Scene* sc;
	std::vector<std::vector<std::vector<int>>> loaded;
	std::vector<std::vector<int>> AllLeves;
public:
	Gen(Scene* scene) {
		lvl = new Level(1, 1);
		sc = scene;
	}
	~Gen() { delete lvl; }
	Level* getLevel() { return lvl; }
	void GenerateLevel();
	void DrawLevel(int index, Scene* scene);
	void DrawAllLevels(Scene* scene);
};

