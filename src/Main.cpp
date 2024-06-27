#include "Main.h"

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(600, 650), "Tetris", Style::Titlebar | Style::Close);
	
	read_file();
	read_ini_file();

	menu(window);
	return 0;
}