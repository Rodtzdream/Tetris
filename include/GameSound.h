#ifndef GAMESOUND_H
#define GAMESOUND_H

#include <SFML/Audio.hpp>
#include <string>

class GameSound
{
public:
	GameSound() = default;
	bool loadFromFile(const std::string& filePath);
	void play();
	void stop();
	void setVolume(float volume);

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

#endif // GAMESOUND_H