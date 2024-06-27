#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "GameMusic.h"
#include "GameSound.h"
#include <unordered_map>
#include <memory>
#include <string>

class AudioManager
{
public:
	static AudioManager& getInstance();
	void loadMusic(const std::string& musicName, const std::string& filePath);
	void loadSound(const std::string& soundName, const std::string& filePath);
	void playMusic(const std::string& musicName);
	void stopMusic(const std::string& musicName);
	void playSound(const std::string& soundName);
	void stopSound(const std::string& soundName);

private:
	AudioManager() {}
	~AudioManager() {}

	std::unordered_map<std::string, std::unique_ptr<GameMusic>> musics;
	std::unordered_map<std::string, std::unique_ptr<GameSound>> sounds;
};

#endif // AUDIOMANAGER_H