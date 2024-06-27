#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "GameMusic.h"
#include "GameSound.h"
#include <unordered_map>
#include <memory>
#include <string>

extern float mus_vol_menu;
extern float mus_vol_game;
extern float mus_vol_gen;
extern bool music_on;

class AudioManager
{
public:
	static AudioManager& getInstance();
	void loadMusic(const std::string& musicName, const std::string& filePath);
	void loadSound(const std::string& soundName, const std::string& filePath);
	void playMusic(const std::string& musicName);
	void pauseMusic(const std::string& musicName);
	void stopMusic(const std::string& musicName);
	void playSound(const std::string& soundName);
	void stopSound(const std::string& soundName);
	void setMusicVolume(const std::string& musicName, float volume);
	void setSoundVolume(const std::string& soundName, float volume);
	void setMusicLooping(const std::string& musicName, bool loop);

private:
	AudioManager();
	~AudioManager() {}

	std::unordered_map<std::string, std::unique_ptr<GameMusic>> musics;
	std::unordered_map<std::string, std::unique_ptr<GameSound>> sounds;
};

#endif // AUDIOMANAGER_H