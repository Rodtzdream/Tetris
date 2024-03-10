#pragma once
#include "ini.h"

class SoundSettings
{
public:
	SoundSettings() {
		readIniFile();
	}

	~SoundSettings() {
		writeIniFile();
	}
	void writeIniFile();
	void readIniFile();

protected:
	float mus_vol_menu = 100;
	float mus_vol_game = 100;
	float mus_vol_gen = 100;
	bool music_on = true;
};

