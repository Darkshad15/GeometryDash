#pragma once
#include "Engine.h"
#include <functional>
#include <map>

class GameObject;

using EventCallback = std::function<void()>;
using ClickableCallback = std::function<void(GameObject*)>;

class InputManager
{
private:

    //Dico de Touche
    static std::map<std::string, EventCallback> keyPressCallbacks;
    static std::map<std::string, EventCallback> keyHoldCallbacks;
    static std::map<std::string, bool> previousKeyStates;
    
    //Dico D'objet
    static std::vector<GameObject*> clickableObjects;
    static std::map<GameObject*, ClickableCallback> objectClickCallbacks;
    static std::map<sf::Mouse::Button, bool> previousMouseStates;
    
    //pointeur window
    static sf::RenderWindow* windowRef;


    static sf::Keyboard::Key StringToKey(const std::string& key);
    static bool IsPointInObject(GameObject* obj, sf::Vector2f point);
public:

    //Get
    static sf::Vector2f GetMousePosition();


    //Autres (Key)
    static void RegisterKeyPress(const std::string& key, EventCallback callback);
    static void RegisterKeyHold(const std::string& key, EventCallback callback);
    static bool IsKeyPressed(const std::string& key);

    //Autres (Object)
    static void RegisterClickableObject(GameObject* obj, ClickableCallback callback);
    static void UnregisterClickableObject(GameObject* obj);

    //Autres
    static bool IsMouseButtonPressed(sf::Mouse::Button button);
    static void Initialize(sf::RenderWindow* window);
    static void ProcessInput();
    static void ClearKeyCallbacks();
    static void Clear();   
};