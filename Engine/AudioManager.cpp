#include "Component.h"


AudioManager::AudioManager(std::string s, int i): //Constructeur
	soundBuffer(),sound(soundBuffer)
{
	this->soundPath = s;
	setId(i);
}

void AudioManager::Start() //initialise l'audio
{
	if (!soundBuffer.loadFromFile(soundPath)) {
		std::cout << "erreur avec le chargement du son";
	}
	sound.setBuffer(soundBuffer);
}

void AudioManager::Update()
{

}

void AudioManager::Play() //Joue l'audio
{
	sound.play();
}


void AudioManager::Pause()
{
	sound.pause();
}

void AudioManager::Render(sf::RenderWindow& window)
{

}