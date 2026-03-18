#include "InputManager.h"
#include "GameObject.h"
#include "Component.h"


std::map<std::string, EventCallback> InputManager::keyPressCallbacks;
std::map<std::string, EventCallback> InputManager::keyHoldCallbacks;
std::map<std::string, bool> InputManager::previousKeyStates;

std::map<GameObject*, ClickableCallback> InputManager::objectHoverEnterCallbacks;
std::map<GameObject*, ClickableCallback> InputManager::objectHoverExitCallbacks;
std::map<GameObject*, bool> InputManager::objectHoverStates;

std::map<sf::Mouse::Button, bool> InputManager::previousMouseStates;


std::vector<GameObject*> InputManager::clickableObjects;
std::map<GameObject*, ClickableCallback> InputManager::objectClickCallbacks;


sf::RenderWindow* InputManager::windowRef = nullptr;


void InputManager::Initialize(sf::RenderWindow* window)
{
    windowRef = window;
}


void InputManager::RegisterKeyPress(const std::string& key, EventCallback callback)
{
    keyPressCallbacks[key] = callback;
    previousKeyStates[key] = false;
}

void InputManager::RegisterKeyHold(const std::string& key, EventCallback callback)
{
    keyHoldCallbacks[key] = callback;
}

bool InputManager::IsKeyPressed(const std::string& key)
{
    sf::Keyboard::Key sfKey = StringToKey(key);
    return sf::Keyboard::isKeyPressed(sfKey);
}

bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

sf::Vector2f InputManager::GetMousePosition()
{
    if (windowRef == nullptr)
        return sf::Vector2f(0, 0);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(*windowRef);
    sf::Vector2i absPos = sf::Mouse::getPosition();  // position absolue écran
    sf::Vector2i winPos = windowRef->getPosition();  // position de la fenêtre

    return sf::Vector2f((float)pixelPos.x, (float)pixelPos.y);
}

void InputManager::RegisterClickableObject(GameObject* obj, ClickableCallback callback)
{
    if (obj == nullptr)
        return;
    
    auto it = std::find(clickableObjects.begin(), clickableObjects.end(), obj);
    if (it == clickableObjects.end())
    {
        clickableObjects.push_back(obj);
    }
    
    objectClickCallbacks[obj] = callback;
}

void InputManager::UnregisterClickableObject(GameObject* obj)
{

    auto it = std::find(clickableObjects.begin(), clickableObjects.end(), obj);
    if (it != clickableObjects.end())
    {
        clickableObjects.erase(it);
    }
    

    objectClickCallbacks.erase(obj);
}

void InputManager::RegisterHoverObject(GameObject* obj, ClickableCallback onEnter, ClickableCallback onExit)
{
    if (obj == nullptr)
        return;

    objectHoverEnterCallbacks[obj] = onEnter;
    objectHoverExitCallbacks[obj] = onExit;
    objectHoverStates[obj] = false;
}


void InputManager::ProcessInput()
{
    for (auto& [key, callback] : keyHoldCallbacks)
    {
        if (IsKeyPressed(key))
        {
            callback();
        }
    }
    
    for (auto& [key, callback] : keyPressCallbacks)
    {
        bool currentState = IsKeyPressed(key);
        bool wasPressed = previousKeyStates[key];
        
        if (currentState && !wasPressed)
        {
            callback();
        }
        
        if(previousKeyStates.contains(key))
            previousKeyStates[key] = currentState;
    }

    
    sf::Vector2f mousePos = GetMousePosition();
    for (GameObject* obj : clickableObjects)
    {
        if (obj == nullptr) continue;
        
        bool isHovered = IsPointInObject(obj, mousePos);
        bool wasHovered = objectHoverStates[obj];

        if (isHovered && !wasHovered)
        {
            objectHoverStates[obj] = true;
            auto it = objectHoverEnterCallbacks.find(obj);
            if (it != objectHoverEnterCallbacks.end())
                it->second(obj);
        }
        else if (!isHovered && wasHovered)
        {
            objectHoverStates[obj] = false;
            auto it = objectHoverExitCallbacks.find(obj);
            if (it != objectHoverExitCallbacks.end())
                it->second(obj);
        }
    }

    
    bool leftMousePressed = IsMouseButtonPressed(sf::Mouse::Button::Left);
    bool wasLeftMousePressed = previousMouseStates[sf::Mouse::Button::Left];
    
    if (leftMousePressed && !wasLeftMousePressed)
    {
        sf::Vector2f mousePos = GetMousePosition();
        std::cout << "Clic! pos: " << mousePos.x << "," << mousePos.y << " nb objets: " << clickableObjects.size() << std::endl;

        for (GameObject* obj : clickableObjects)
        {
            if (obj != nullptr)
                std::cout << "obj clickable: " << obj->getClickable()
                << " inBounds: " << IsPointInObject(obj, mousePos)
                << " pos: " << obj->getTransform().pos.x << "," << obj->getTransform().pos.y
                << " hasCallback: " << (objectClickCallbacks.find(obj) != objectClickCallbacks.end())
                << std::endl;
        }

        for (GameObject* obj : clickableObjects)
        {
            if (obj != nullptr && IsPointInObject(obj, mousePos) && obj->getClickable() == true)
            {
                auto it = objectClickCallbacks.find(obj);
                if (it != objectClickCallbacks.end())
                {
                    it->second(obj);
                    break;
                }
            }
        }
    }
    previousMouseStates[sf::Mouse::Button::Left] = leftMousePressed;
}


bool InputManager::IsPointInObject(GameObject* obj, sf::Vector2f point)
{
    if (obj == nullptr || !obj->getClickable()) 
        return false;

    Text* textComponent = obj->GetComponent<Text>();
    if (textComponent != nullptr)
    {
        sf::FloatRect bounds = textComponent->getSFText().getGlobalBounds();
        return (point.x >= bounds.position.x &&
            point.x <= bounds.position.x + bounds.size.x &&
            point.y >= bounds.position.y &&
            point.y <= bounds.position.y + bounds.size.y);
    }

    SpriteRenderer* spriteComponent = obj->GetComponent<SpriteRenderer>();
    if (spriteComponent != nullptr)
    {
        sf::FloatRect bounds = spriteComponent->getSprite().getGlobalBounds();

        return (point.x >= bounds.position.x &&
            point.x <= bounds.position.x + bounds.size.x &&
            point.y >= bounds.position.y &&
            point.y <= bounds.position.y + bounds.size.y);
    }

    return false;
}

void InputManager::ClearKeyCallbacks()
{
    keyPressCallbacks.clear();
    keyHoldCallbacks.clear();
    previousKeyStates.clear();
}
    
void InputManager::Clear()
{
    keyPressCallbacks.clear();
    keyHoldCallbacks.clear();
    previousKeyStates.clear();
    
    clickableObjects.clear();
    objectClickCallbacks.clear();
    previousMouseStates.clear();

    objectHoverStates.clear();
    objectHoverEnterCallbacks.clear();
    objectHoverExitCallbacks.clear();

}

sf::Keyboard::Key InputManager::StringToKey(const std::string& key)
{
    static std::map<std::string, sf::Keyboard::Key> keyMap = {
        {"A", sf::Keyboard::Key::A}, {"B", sf::Keyboard::Key::B},
        {"C", sf::Keyboard::Key::C}, {"D", sf::Keyboard::Key::D},
        {"E", sf::Keyboard::Key::E}, {"F", sf::Keyboard::Key::F},
        {"G", sf::Keyboard::Key::G}, {"H", sf::Keyboard::Key::H},
        {"I", sf::Keyboard::Key::I}, {"J", sf::Keyboard::Key::J},
        {"K", sf::Keyboard::Key::K}, {"L", sf::Keyboard::Key::L},
        {"M", sf::Keyboard::Key::M}, {"N", sf::Keyboard::Key::N},
        {"O", sf::Keyboard::Key::O}, {"P", sf::Keyboard::Key::P},
        {"Q", sf::Keyboard::Key::Q}, {"R", sf::Keyboard::Key::R},
        {"S", sf::Keyboard::Key::S}, {"T", sf::Keyboard::Key::T},
        {"U", sf::Keyboard::Key::U}, {"V", sf::Keyboard::Key::V},
        {"W", sf::Keyboard::Key::W}, {"X", sf::Keyboard::Key::X},
        {"Y", sf::Keyboard::Key::Y}, {"Z", sf::Keyboard::Key::Z},
        {"0", sf::Keyboard::Key::Num0}, {"1", sf::Keyboard::Key::Num1},
        {"2", sf::Keyboard::Key::Num2}, {"3", sf::Keyboard::Key::Num3},
        {"4", sf::Keyboard::Key::Num4}, {"5", sf::Keyboard::Key::Num5},
        {"6", sf::Keyboard::Key::Num6}, {"7", sf::Keyboard::Key::Num7},
        {"8", sf::Keyboard::Key::Num8}, {"9", sf::Keyboard::Key::Num9},
        {"Space", sf::Keyboard::Key::Space},
        {"Enter", sf::Keyboard::Key::Enter},
        {"Escape", sf::Keyboard::Key::Escape},
        {"Backspace", sf::Keyboard::Key::Backspace},
        {"Tab", sf::Keyboard::Key::Tab},
        {"Up", sf::Keyboard::Key::Up},
        {"Down", sf::Keyboard::Key::Down},
        {"Left", sf::Keyboard::Key::Left},
        {"Right", sf::Keyboard::Key::Right},
        {"F1", sf::Keyboard::Key::F1}, {"F2", sf::Keyboard::Key::F2},
        {"F3", sf::Keyboard::Key::F3}, {"F4", sf::Keyboard::Key::F4},
        {"F5", sf::Keyboard::Key::F5}, {"F6", sf::Keyboard::Key::F6},
        {"F7", sf::Keyboard::Key::F7}, {"F8", sf::Keyboard::Key::F8},
        {"F9", sf::Keyboard::Key::F9}, {"F10", sf::Keyboard::Key::F10},
        {"F11", sf::Keyboard::Key::F11}, {"F12", sf::Keyboard::Key::F12},
        {"LShift", sf::Keyboard::Key::LShift},
        {"RShift", sf::Keyboard::Key::RShift},
        {"LControl", sf::Keyboard::Key::LControl},
        {"RControl", sf::Keyboard::Key::RControl},
        {"LAlt", sf::Keyboard::Key::LAlt},
        {"RAlt", sf::Keyboard::Key::RAlt}
    };
    
    auto it = keyMap.find(key);
    if (it != keyMap.end())
        return it->second;
    
    return sf::Keyboard::Key::Unknown;
}