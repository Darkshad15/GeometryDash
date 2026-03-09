#pragma once
#include "Engine.h"
#include "Component.h"
#include "Transform.h"

class Component;



class GameObject
{
private:

	Scene* owner;
	std::string name;
	bool active;
	Transform transform;
	std::vector<Component*> components;
	bool markedForDestruction = false;
	bool clickable = false;


public:

	//Constructeurs
	GameObject(sf::Vector2f position);

	//Get
	bool getClickable() { return clickable; }
	bool getActive() { return active; }
	Scene* getOwner() { return owner; }
	Transform& getTransform();
	template<typename T>
	T* GetComponent(size_t index = 0)
	{
		size_t count = 0;
		for (Component* component : components)
		{
			if (T* casted = dynamic_cast<T*>(component))
			{
				if (count == index)
					return casted;
				++count;
			}
		}
		return nullptr;
	}


	

	//Set
	void setClickable(bool B) { clickable = B; }
	void setOwner(Scene* s);
	void SetPosition(sf::Vector2f pos);
	
	//Autres
	Component* AddComponent(Component* component);
	void Start();
	void Update();
	void Render(sf::RenderWindow& window);
	void Destroy();

	bool IsMarkedForDestruction() const {return markedForDestruction;}
	
	
};

