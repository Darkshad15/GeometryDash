#include "Level.h"

Level::Level(int diff, int ord) {
    difficulty = diff;
    order = ord;
    elem = new Elements();
}

Level::~Level() {
    delete elem;
}

std::vector<std::vector<int>> Level::Load(const std::string& chemin) {
    LevelParts.clear();
    std::ifstream fichier(chemin);

    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir " << chemin << std::endl;
        return LevelParts;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::vector<int> rangee;
        std::istringstream stream(ligne);
        int valeur;

        while (stream >> valeur) {
            rangee.push_back(valeur);
        }

        if (!rangee.empty())
            LevelParts.push_back(rangee);
    }

    fichier.close();
    return LevelParts;
}

void Level::Draw(Scene* scene) {
    for (int y = 0; y < LevelParts.size(); y++) {
        for (int x = 0; x < LevelParts[y].size(); x++) {

            GameObject* obj = nullptr;

            switch (LevelParts[y][x]) {
            case 0: obj = elem->createEmpty(); break;
            case 1: obj = elem->createBlock(); break;
            case 2: obj = elem->createSpike(); break;
            default: break;
            }

            if (obj) {
                obj->SetPosition({ (float)x * 64, (float)y * 64 });
                scene->AddGameObject(obj); 
                spawnedObjects.push_back(obj);
            }
        }
    }
}