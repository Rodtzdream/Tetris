#pragma once
#include "SoundSettings.h"
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager : public SoundSettings
{
public:
	SoundManager() : SoundSettings() 
	{
		game_music.openFromFile("resources/game.flac");
		menu_music.openFromFile("resources/menu.flac");
		game_music.setLoop(true);
		menu_music.setLoop(true);
		game_music.setVolume(mus_vol_game);
		menu_music.setVolume(mus_vol_game);

		buffer1.loadFromFile("resources/destruction.flac");
		buffer2.loadFromFile("resources/switch.wav");
		buffer3.loadFromFile("resources/select.wav");
		buffer4.loadFromFile("resources/gameover.flac");

		destruction_sound.setBuffer(buffer1);
		destruction_sound.setLoop(false);
		destruction_sound.setVolume(mus_vol_menu);
		switch_sound.setBuffer(buffer2);
		switch_sound.setLoop(false);
		switch_sound.setVolume(mus_vol_menu);
		select_sound.setBuffer(buffer3);
		select_sound.setLoop(false);
		select_sound.setVolume(mus_vol_menu);
		gameover_sound.setBuffer(buffer4);
		gameover_sound.setLoop(false);
		gameover_sound.setVolume(mus_vol_menu);
	}
private:
	Music game_music;
	Music menu_music;
	SoundBuffer buffer1, buffer2, buffer3, buffer4;
	Sound destruction_sound;
	Sound switch_sound;
	Sound select_sound;
	Sound gameover_sound;
};