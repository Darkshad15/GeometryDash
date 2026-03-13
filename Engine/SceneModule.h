#pragma once
#include "SFML/Graphics.hpp"


class Scene;

class SceneModule
{

private:
	Scene* activeScene;
	sf::RenderWindow window;
	std::string name;

	Scene* pendingScene = nullptr;  
	bool sceneChanged = false;

public:

	//Constructeurs
	SceneModule();
	SceneModule(sf::Vector2u size,std::string name);

	//Get
	sf::RenderWindow& getWindow() { return window; }
	Scene* GetActiveScene();

	//Set
	void SetActiveScene(Scene* scene);
	void SetPendingScene(Scene* scene) { pendingScene = scene;  sceneChanged = true;}

	//Autres
	void Start();
	void Update();
};

