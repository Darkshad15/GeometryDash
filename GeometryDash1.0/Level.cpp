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


void Level::Draw(Scene* scene, std::vector<std::vector<int>> part, float offsetX = 0.f) {
    for (int y = 0; y < part.size(); y++) {
        for (int x = 0; x < part[y].size(); x++) {

            GameObject* obj = nullptr;

            switch (part[y][x]) {
            case 0: obj = elem->createEmpty(); break;
            case 1: obj = elem->createBlock(); break;
            case 2: obj = elem->createSpike(); break;
            default: break;
            }

            if (obj) {
                float posX = (float)x * 64 + offsetX;
                float posY = (float)y * 64;

                
                if (part[y][x] == 2) {
                    Shape* shape = obj->GetComponent<Shape>();
                    if (shape) {
                        sf::FloatRect bounds = shape->getBounds();
                        posX = (float)x * 64 + 28.f + offsetX;
                        posY = (float)(y + 1) * 64 - bounds.size.y;
                    }
                }

                obj->SetPosition({ posX, posY });
                scene->AddGameObject(obj);
                spawnedObjects.push_back(obj);
            }
        }
    }
}

void Level::Move(float deltaTime)
{
    for (GameObject* obj : spawnedObjects)
    {
        obj->getTransform().pos.x -= 300.f * deltaTime; // 200 pixels/seconde
    }
}