#include "SceneModule.h"
#include "Scene.h"



SceneModule::SceneModule()
{
	name = "default";
	window = sf::RenderWindow(sf::VideoMode({800,800}), "default");
	window.setFramerateLimit(60);
}


SceneModule::SceneModule(sf::Vector2u size,std::string name)
{
	this->name = name;
	window = sf::RenderWindow(sf::VideoMode(size),name);
}

void SceneModule::SetActiveScene(Scene* scene)
{
	activeScene = scene;
	window.setSize(scene->getSize());
	window.setTitle(name+" : "+scene->getName());
}

Scene* SceneModule::GetActiveScene()
{
	return activeScene;
}

void SceneModule::Start()
{
	InputManager::Initialize(&window);
	if (activeScene != nullptr)
		activeScene->Start();
	Update();
}

void SceneModule::Update()
{
	while (window.isOpen())
	{

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		InputManager::ProcessInput();
		Event::ProcessEvent();

		window.clear();

		if (activeScene != nullptr)
			activeScene->Update(window);

	}
}