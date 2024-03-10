#include "SoundSettings.h"

void SoundSettings::writeIniFile()
{
	mINI::INIFile file_coonfig("music_sounds_coonfig.ini");
	mINI::INIStructure data;

	data["options"]["general_volume"] = std::to_string(mus_vol_gen);
	data["options"]["music_volume"] = std::to_string(mus_vol_game);
	data["options"]["sounds_volume"] = std::to_string(mus_vol_menu);
	data["options"]["music_on"] = std::to_string(music_on);

	file_coonfig.generate(data);
}

void SoundSettings::readIniFile()
{
	mINI::INIFile file_coonfig("music_sounds_coonfig.ini");
	mINI::INIStructure data;

	file_coonfig.read(data);

	std::string temp = data.get("options").get("general_volume");
	mus_vol_gen = std::stof(temp);
	temp = data.get("options").get("music_volume");
	mus_vol_game = std::stof(temp);
	temp = data.get("options").get("sounds_volume");
	mus_vol_menu = std::stof(temp);

	temp = data.get("options").get("music_on");
	music_on = std::stof(temp);
}