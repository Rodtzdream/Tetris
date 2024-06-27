#include "GameSound.h"

bool GameSound::loadFromFile(const std::string& filePath)
{
	return buffer.loadFromFile(filePath);
}

void GameSound::play()
{
	sound.setBuffer(buffer);
	sound.play();
}

void GameSound::stop()
{
	sound.stop();
}

void GameSound::setVolume(float volume)
{
	sound.setVolume(volume);
}