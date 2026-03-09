#include "Engine.h"

void Engine::Start() //Lance le moteur et tous ses modules
{
	sceneModule->Start();
}

void Engine::Update() //Update le moteur et tous ses modules
{
	sceneModule->Update();
}


Engine::Engine() //Constructeur par défaut
{
	this->sceneModule = new SceneModule();
	GameState = true;
}

Engine::Engine(sf::Vector2u size,std::string name) // Constructeurs a 2 param (taille de la fenetre, nom du jeu)
{
	this->sceneModule = new SceneModule(size,name);
}