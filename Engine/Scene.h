#pragma once
#include "GameObject.h"

class GameObject;



class Scene
{
private:
	sf::Clock clock;
	std::string name;
	std::vector<GameObject*> objects;
	sf::Vector2u size = { 800,800 };
	GameObject* player = nullptr;
	GameObject* LvLData = nullptr;
public:

	//Constructeurs
	Scene(std::string name, sf::Vector2u size = { 800,800 });

	//Get
	std::vector<GameObject*> getLstObj() { return objects; }
	GameObject* getThisObjByText(std::string name);
	bool LvlEnd() { if (clock.getElapsedTime().asSeconds() > 5 && name == "LvL1") return true; else return false; }
	sf::Vector2u getSize() { return size; }
	std::string getName() { return name; }
	GameObject* GetPlayer() { return player; }
	GameObject* GetLvLData() { return LvLData; }

	//Set
	void SetPlayer(GameObject* p) { player = p; }
	void SetLvLData(GameObject* Lvl) { LvLData = Lvl; }

	//Autres
	void Destroy();
	void RemoveGameObject(GameObject* obj);
	void AddGameObject(GameObject* obj);
	void Start();
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);

	void CleanupDestroyedObjects();
	
};

