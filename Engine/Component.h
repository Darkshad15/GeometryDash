#pragma once
#include "GameObject.h"

class GameObject;

class Component
{	

protected:
	GameObject* owner;
	int id;
public:
	int getId() { return id; }
	void setId(int i) { id = i; }
	Component() : owner(nullptr) {}   
	virtual ~Component() {}
	void setOwner(GameObject *o);
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
};


class SpriteRenderer : public Component
{
private:
	bool Special = false;
	std::string texturePath;
	sf::Texture texture;
	sf::Sprite sprite;
	int currentFrame = 0;
	sf::Clock animationClock;
	sf::Vector2i size;
	std::array<int, 2> AnimationParam;
	bool animated = false;
	bool visible = true;
	Direction direction;
public:
	
	//Constructeurs
	SpriteRenderer();
	SpriteRenderer(std::string s, sf::Vector2i size, std::array<int, 2> tab,bool b = false, int id = 0);

	//Get
	Direction getDirection() { return direction; }
	bool getAnimated() { return animated; }
	sf::FloatRect getBounds() { return sprite.getGlobalBounds(); }
	bool getVisible() { return visible; }

	sf::Sprite& getSprite() { return sprite; }

	//Set
	void setDirection(Direction d) { direction = d; }
	void setFond(bool B);
	void setAnimated(bool B) { animated = B; }
	void setVisible(bool B) { visible = B; }
	void UpFrame() { currentFrame = (currentFrame + 1) % AnimationParam[1]; }
	void DownFrame() { currentFrame = (currentFrame - 1 + AnimationParam[1]) % AnimationParam[1]; }
	void setScale(float f) { sprite.setScale({ f,f }); }
	void setCenterOrigin();

	//Autres
	void Start() override;
	void Update() override;
	virtual void Render(sf::RenderWindow& window) override;


};

class Text : public Component
{
private:
	sf::Font font;
	sf::Text text;
	std::string txt;
public:

	//Constructeurs
	Text();
	Text(std::string text, int size = 30, sf::Color color = sf::Color::White, std::string font = "arial.ttf");

	//Get
	sf::Text& getSFText() { return text; }
	std::string getText() { return txt; }
	sf::FloatRect getBounds() { return text.getLocalBounds(); }

	//Set
	void setText(std::string text) { txt = text; }

	//Autres
	void Start() override;
	void Update() override;
	virtual void Render(sf::RenderWindow& window) override;
};




class AudioManager : public Component
{
private:
	std::string soundPath;
	sf::SoundBuffer	soundBuffer;
	sf::Sound sound;
public:
	//Constructeurs
	AudioManager(std::string s,int id = 0);

	//Set
	void SetLoop(bool B) { sound.setLooping(B); }

	//Autres
	void Start() override;
	void Update() override;
	void Play();
	void Render(sf::RenderWindow& window) override;
	void Pause();
};

class Player : public Component
{
private:
	Direction direction = Direction::Down;;
	float s;
public:

	//Constructeurs
	Player(float speed);
	

	//Autres
	void Start();
	void Update() override;
	void Render(sf::RenderWindow& window) override;
};


class Projectile : public Component
{
private:
	GameObject* shootOwner;
	Direction direction = Direction::Up;
	float speed;
	sf::Vector2f directionVector;
public:

	//Constructeurs
	Projectile(float speed, Direction direction,GameObject* shootOwner);
	Projectile(sf::Vector2f target, float speed,sf::Vector2f start, GameObject* shootOwner);
	//Get
	Direction getDirection();
	GameObject* getShooter() { return shootOwner; }

	//Set
	void setDirection(Direction d) { direction = d; }

	//Autres
	void Start();
	void Update() override;
	void Render(sf::RenderWindow& window) override;
};


class Variables : public Component
{
private:
	std::map<std::string, int> integers;
	std::map<std::string, float> floats;
	std::map<std::string, double> doubles;
	std::map<std::string, std::string> strings;
public:
	void addInt(std::string name, int value);
	void addFloat(std::string name, float value);
	void addDouble(std::string name, double value);
	void addString(std::string name, std::string value);

	int getInt(std::string name) {{if (integers.find(name) != integers.end()) {return integers[name];} return 0;}};
	float getFloat(std::string name) {{if(floats.find(name) != floats.end()) { return floats[name]; } return 0;}};
	double getDouble(std::string name) {{if(doubles.find(name) != doubles.end()) { return doubles[name];} return 0;}};
	void PlusInt(std::string name, int i) { if (integers.find(name) != integers.end()) { integers[name] += i; } };
	void MinusInt(std::string name, int i) { if (integers.find(name) != integers.end()) { integers[name] -= i; } };
	std::string getString(std::string name) {{if(strings.find(name) != strings.end()) { return strings[name]; } return "NUL"; } };

	void Start() override {}
	void Update() override {}
	void Render(sf::RenderWindow& window) override {}
};


class Movement : public Component {
private:
	float speed;
public:
	Movement(float s) : speed(s) {}
	void Start();
	void Update();
	void Render(sf::RenderWindow& window);
};


class Collider : public Component 
{
private:
	bool canCollide = true;

public:
	//Constructeurs
	Collider() {};
	bool getCollide() { return canCollide; }
	void setCollide(bool t) { canCollide = t; }
	void Start() override;
	void Update() override;
	void Render(sf::RenderWindow& window);




	bool DoesCollide(GameObject* target);

};

class Ennemie : public Component
{
	void Start() override;
	void Update() override;
	void Render(sf::RenderWindow& window);
};


class NewClock : public Component
{
private:
	sf::Clock clock;
public:
	void StartClock();
	void StopClock();
	void ResetClock();
	float GetTimeSinceStart() { return clock.getElapsedTime().asSeconds(); };
	

	void Start() override {}
	void Update() override {}
	void Render(sf::RenderWindow& window) override {}
};