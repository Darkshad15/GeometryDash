#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
#include "Scene.h"
#include "Scenes.h"

unsigned int screenW = 800.0f;
unsigned int screenH = 600.0f;

float centerX = screenW / 2.0f;
float centerY = screenH / 2.0f;

int main()
{

    Engine engine({ screenW, screenH }, "Mon Premier Jeu");

    Scenes scenes;
    scenes.Start();

    engine.Start();
   

    return 0;

}