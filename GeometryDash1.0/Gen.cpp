#include "Gen.h"

void Gen::GenerateLevel()
{
    loaded.clear(); 
	srand(time(0));
    for (int i = 0; i < 9; i++) 
    {
        int variante = rand() % 5; 
        std::string fichier = "Assets/" + std::to_string(i) + std::to_string(variante) + ".txt";
		std::cout << "level " + std::to_string(i) + std::to_string(variante) + " charge" << std::endl;
        AllLeves = lvl->Load(fichier);
        if (!AllLeves.empty())
            loaded.push_back(AllLeves);
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

void Gen::DrawAllLevels(Scene* scene)
{
	for (int i = 0; i < loaded.size(); i++)
	{
		DrawLevel(i, scene);
	}
}