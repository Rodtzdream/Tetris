#include "AudioManager.h"

AudioManager& AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}

void AudioManager::loadMusic(const std::string& musicName, const std::string& filePath)
{
	auto music = std::make_unique<GameMusic>();
	if (music->loadFromFile(filePath))
	{
		musics[musicName] = std::move(music);
	}
}

void AudioManager::loadSound(const std::string& soundName, const std::string& filePath)
{
	auto sound = std::make_unique<GameSound>();
	if (sound->loadFromFile(filePath))
	{
		sounds[soundName] = std::move(sound);
	}
}

void AudioManager::playMusic(const std::string& musicName)
{
	auto it = musics.find(musicName);
	if (it != musics.end())
	{
		it->second->play();
	}
}

void AudioManager::stopMusic(const std::string& musicName)
{
	auto it = musics.find(musicName);
	if (it != musics.end())
	{
		it->second->stop();
	}
}

void AudioManager::playSound(const std::string& soundName)
{
	auto it = sounds.find(soundName);
	if (it != sounds.end())
	{
		it->second->play();
	}
}

void AudioManager::stopSound(const std::string& soundName)
{
	auto it = sounds.find(soundName);
	if (it != sounds.end())
	{
		it->second->stop();
	}
}