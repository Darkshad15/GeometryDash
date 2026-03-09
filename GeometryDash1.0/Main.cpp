#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Engine.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    Block* carre = new Block();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        carre->draw(window);
        window.display();
    }
}