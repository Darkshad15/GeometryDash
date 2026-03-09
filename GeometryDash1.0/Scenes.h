#pragma once
#include "Scene.h"
#include <iostream>
#include<vector>


class Scenes
{
private:
	std::vector<Scene>* _scene;

public:


	//Scene* Update(std::vector<Scene>* _scene);


	Scene* CreateMain();
	Scene* CreateLevel();
	Scene* CreatePause();
	Scene* CreateGameover();
	

};

