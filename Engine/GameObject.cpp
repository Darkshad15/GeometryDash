#include "GameObject.h"


GameObject::GameObject(sf::Vector2f position) //Constructeur (position de l'objet)
{
    this->getTransform().pos.x = position.x;
    this->getTransform().pos.y = position.y;
    active = true;
}

Transform& GameObject::getTransform()
{
	return transform;
}

void GameObject::Start() //Init tous les composants de l'objet
{
    for (Component* component : components)
    {
        if (component != nullptr)
        {
            component->Start();
        }
    }
    
}

void GameObject::Update() {
    for (Component* component : components)
    {
        if (component != nullptr)
        {
            component->Update();
        }
        else
        {
            std::cout << "[ERROR] Composant null dans Update!" << std::endl;
        }
    }
}

void GameObject::Render(sf::RenderWindow& window) {
    for (Component* component : components)
    {
        if (component != nullptr)
        {
            component->Render(window);
        }
        else
        {
            std::cout << "[ERROR] Composant null dans Render!" << std::endl;
        }
    }
}

void GameObject::SetPosition(sf::Vector2f pos) 
{
    getTransform().pos.x = pos.x;
    getTransform().pos.y = pos.y;
}

Component* GameObject::AddComponent(Component* component) //Ajoute un composant 
{
    component->setOwner(this);
    components.push_back(component);
    return component;
}

void GameObject::setOwner(Scene* s) 
{
    this->owner = s;
}

void GameObject::Destroy() {
    markedForDestruction = true;
}
