#ifndef GAMEMUSIC_H
#define GAMEMUSIC_H

#include <SFML/Audio.hpp>
#include <string>

class GameMusic
{
public:
	GameMusic() = default;
	bool loadFromFile(const std::string& filePath);
	void play();
	void stop();
	void setLoop(bool loop);
	void setVolume(float volume);

private:
	sf::Music music;
};

#endif // GAMEMUSIC_H