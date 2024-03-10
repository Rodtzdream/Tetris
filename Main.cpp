#include "Main.h"

int main()
{
	srand(time(NULL));

	int scrX = GetSystemMetrics(SM_CXSCREEN);
	int scrY = GetSystemMetrics(SM_CYSCREEN);
	RenderWindow window(VideoMode(600, 650), "Tetris", Style::Titlebar | Style::Close);
	if (scrX == 1360 && scrY == 768)
		window.setPosition(Vector2i(380, 25));

	readFile();

	readIniFile();
	menu(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
	return 0;
}