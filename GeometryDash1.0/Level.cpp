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
            case 0: continue;
            case 1: obj = elem->createBlock(); break;
            case 2: obj = elem->createSpike(); break;
            case 3: obj = elem->createCircle(); break;
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
                //obj->SetPosition({ posX, posY });
                //cene->AddGameObject(obj);
                //spawnedObjects.push_back(obj);
                startPositions.push_back({ posX, posY });
            }
        }
    }
}

void Level::Move(float deltaTime)
{
    for (GameObject* obj : spawnedObjects)
    {
        obj->getTransform().pos.x -= 300.f * deltaTime;


        float x = obj->getTransform().pos.x;
        Shape* shape = obj->GetComponent<Shape>();

        if (shape != nullptr)
        {
            if (x < -64.f || x > 2064.f)
                shape->setVisible(false);
            else
                shape->setVisible(true);
        }
        if (x < -64.f || x > 2064.f)
            obj->setActive(false);
        else
            obj->setActive(true);
    }
}

void Level::Reset() {
    // On parcourt tous les objets générés
    for (size_t i = 0; i < spawnedObjects.size(); i++) {
        if (spawnedObjects[i] != nullptr) {

            // 1. On remet le bloc exactement là où il a sponné
            spawnedObjects[i]->SetPosition(startPositions[i]);

            // 2. On le réactive (au cas où il était passé hors de l'écran à gauche)
            spawnedObjects[i]->setActive(true);
            Shape* shape = spawnedObjects[i]->GetComponent<Shape>();
            if (shape != nullptr) {
                shape->setVisible(true);
            }
        }
    }
}