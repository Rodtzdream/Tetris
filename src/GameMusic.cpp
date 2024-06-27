#include "GameMusic.h"

bool GameMusic::loadFromFile(const std::string& filePath)
{
	return music.openFromFile(filePath);
}

void GameMusic::play()
{
	music.play();
}

void GameMusic::pause()
{
	music.pause();
}

void GameMusic::stop()
{
	music.stop();
}

void GameMusic::setLoop(bool loop)
{
	music.setLoop(loop);
}

void GameMusic::setVolume(float volume)
{
	music.setVolume(volume);
}