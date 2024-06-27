#include "AudioManager.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

AudioManager::AudioManager()
{
	loadMusic("game", std::string(XSTRING(SOURCE_ROOT)) + "/resources/game.flac");
	loadMusic("menu", std::string(XSTRING(SOURCE_ROOT)) + "/resources/menu.flac");
	loadSound("destruction", std::string(XSTRING(SOURCE_ROOT)) + "/resources/destruction.flac");
	loadSound("switch", std::string(XSTRING(SOURCE_ROOT)) + "/resources/switch.wav");
	loadSound("select", std::string(XSTRING(SOURCE_ROOT)) + "/resources/select.wav");
	loadSound("gameover", std::string(XSTRING(SOURCE_ROOT)) + "/resources/gameover.flac");

	setMusicLooping("game", true);
	setMusicLooping("menu", true);
}

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

void AudioManager::pauseMusic(const std::string& musicName)
{
	auto it = musics.find(musicName);
	if (it != musics.end())
	{
		it->second->pause();
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

void AudioManager::setMusicVolume(const std::string& musicName, float volume)
{
	auto it = musics.find(musicName);
	if (it != musics.end())
	{
		it->second->setVolume(volume);
	}
}

void AudioManager::setSoundVolume(const std::string& soundName, float volume)
{
	auto it = sounds.find(soundName);
	if (it != sounds.end())
	{
		it->second->setVolume(volume);
	}
}

void AudioManager::setMusicLooping(const std::string& musicName, bool loop)
{
	auto it = musics.find(musicName);
	if (it != musics.end())
	{
		it->second->setLoop(loop);
	}
}

void AudioManager::onMusic()
{
	setMusicVolume("game", mus_vol_game * (mus_vol_gen / 100));
	setMusicVolume("menu", mus_vol_game * (mus_vol_gen / 100));
	setSoundVolume("destruction", mus_vol_menu * (mus_vol_gen / 100));
	setSoundVolume("switch", mus_vol_menu * (mus_vol_gen / 100));
	setSoundVolume("select", mus_vol_menu * (mus_vol_gen / 100));
	setSoundVolume("gameover", mus_vol_menu * (mus_vol_gen / 100));
}

void AudioManager::offMusic()
{
	setMusicVolume("game", 0);
	setMusicVolume("menu", 0);
	setSoundVolume("destruction", 0);
	setSoundVolume("switch", 0);
	setSoundVolume("select", 0);
	setSoundVolume("gameover", 0);
}