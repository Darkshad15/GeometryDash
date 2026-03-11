#include "Gen.h"

void Gen::GenerateLevel()
{
	
	for (int i = 0; i < 10; i++) {
		for (int i = 0; i < 10; i++) {
			AllLeves = lvl->Load("Assets/" + std::to_string(i) + ".txt");
			if (!AllLeves.empty())
				loaded.push_back(AllLeves);
		}
	}

	
}


void Gen::DrawLevel(int index, Scene* scene)
{
	if (index >= loaded.size()) return;

	float offsetX = 0.f;

	for (int i = 0; i < index; i++) {
		if (!loaded[i].empty())
			offsetX += loaded[i][0].size() * 64.f;
	}

	lvl->Draw(scene, loaded[index], offsetX);
}