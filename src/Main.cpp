#include "Main.h"
#include <AudioManager.h>

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(600, 650), "Tetris", Style::Titlebar | Style::Close);
	
	read_file();
	read_ini_file();

	AudioManager& audioManager = AudioManager::getInstance();

	audioManager.playMusic("menu");

	//menu(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
	return 0;
}