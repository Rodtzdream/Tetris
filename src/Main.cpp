#include "Main.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(600, 650), "Tetris", Style::Titlebar | Style::Close);

	Music game_music, menu_music;

	game_music.openFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/game.flac");
	menu_music.openFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/menu.flac");
	game_music.setLoop(true);
	menu_music.setLoop(true);
	game_music.setVolume(mus_vol_game);
	menu_music.setVolume(mus_vol_game);

	SoundBuffer buffer1, buffer2, buffer3, buffer4;
	Sound destruction_sound, switch_sound, select_sound, gameover_sound;

	buffer1.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/destruction.flac");
	buffer2.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/switch.wav");
	buffer3.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/select.wav");
	buffer4.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/gameover.flac");

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

	read_file();

	read_ini_file();
	menu(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
	return 0;
}