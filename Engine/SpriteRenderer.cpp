#include "Component.h"

SpriteRenderer::SpriteRenderer():
	sprite(texture)
{

}

SpriteRenderer::SpriteRenderer(std::string s,sf::Vector2i size, std::array<int, 2> tab, bool b, int id) :
	sprite(texture)
{
	texturePath = s;
	this->size = size;
	AnimationParam = tab;
	std::cout << "Loading texture: " << texturePath << std::endl;
	Special = b;
	setId(id);
}

void SpriteRenderer::setCenterOrigin()
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
}

void SpriteRenderer::Start()
{
	if (!texture.loadFromFile(texturePath)) {
		std::cout << "erreur avec le chargement de la texture " << texturePath;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0,0 }, size));
}

void SpriteRenderer::Update()
{
	float x = owner->getTransform().pos.x;
	float y = owner->getTransform().pos.y;
	sprite.setPosition({ x,y });
}


void SpriteRenderer::Render(sf::RenderWindow& window)
{
	if (Special == false)
	{
		if (!texture.isRepeated())
		{
			if (animated == true)
			{
				if (getDirection() == Direction::Left)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						currentFrame = (currentFrame + 1) % AnimationParam[0];
						sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, 0 }, { size.x, size.x }));
						animationClock.restart();
					}
				}
				else if (getDirection() == Direction::Right)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						currentFrame = (currentFrame + 1) % AnimationParam[0];
						sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x % (AnimationParam[1] * size.x) }, { size.x, size.x }));
						animationClock.restart();
					}
				}
				else if (getDirection() == Direction::Up)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						currentFrame = (currentFrame + 1) % AnimationParam[0];
						sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x * 2 % (AnimationParam[1] * size.x) }, { size.x, size.x }));
						animationClock.restart();
					}
				}
				else if (getDirection() == Direction::Down)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						if (AnimationParam[1] < 4)
						{
							currentFrame = (currentFrame + 1) % AnimationParam[0];
							sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x * 2 }, { size.x, size.x }));
							animationClock.restart();
						}
						else
						{
							currentFrame = (currentFrame + 1) % AnimationParam[0];
							sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x * 3 }, { size.x, size.x }));
							animationClock.restart();
						}
					}
				}
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(
					{ 0, currentFrame * size.y },  
					{ size.x, size.y }             
				));
			}
		}
		else
		{
			static float scroll = 0.0f;
			scroll -= 0.008f;
			if (scroll >= size.y)
				scroll = 0.0f;

			sprite.setTextureRect(sf::IntRect({ 0, static_cast<int>(scroll) }, { size.x , size.y  }));
		}
	}
	else
	{
		sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, 0 }, { size.x, size.x }));
		sprite.setPosition({ 650,500 });
	}
	if(visible == true)
		window.draw(sprite);
}


void SpriteRenderer::setFond(bool B)
{
	 texture.setRepeated(B); 
	 sprite.setTexture(texture);


}