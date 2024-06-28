#include "Game.h"
#include "Menu.h"
#include "ReadFile.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

const unsigned short int figures[7][4] = {
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,5,3,7,
	3,5,7,6,
	2,3,4,5,
}; // ������ �������-���������

const int x = 17; // ������ ����
const int y = 26; // ������ ����

unsigned short int field[x][y + 1] = { 0 }; // ������� ���� ��� x � ��� ������ ����, � y � ��� ������.

struct coord
{
	int x, y;

} a[4], b[4], temp[4];

bool gameover()
{
	for (int i = 0; i < 17; i++)
	{
		if (field[i][2] != 0)
			return true;
	}
	return false;
}

void sprite_color(Sprite& sprite, int color)
{
	switch (color)
	{
	case 1:
		sprite.setColor(Color::Red);
		break;
	case 2:
		sprite.setColor(Color::Blue);
		break;
	case 3:
		sprite.setColor(Color::Cyan);
		break;
	case 4:
		sprite.setColor(Color::Yellow);
		break;
	case 5:
		sprite.setColor(Color::Green);
		break;
	}
}

void fill_field(RenderWindow& window, Sprite& sprite_save_figure)
{
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (field[i][j] != 0)
			{
				sprite_save_figure.setPosition(i * 24, j * 24);
				sprite_color(sprite_save_figure, field[i][j]);
				window.draw(sprite_save_figure);
			}
		}
	}
}

bool check_sides(int main_figure, int offsetX, int offsetY, double angle) // �������� �� � ��������� ���� �� ������
{
	if (main_figure == 1 && angle == 180)
		angle = 0;
	int q = cosl(angle / 180.0 * M_PI);
	int w = sinl(angle / 180.0 * M_PI);
	for (int i = 0; i < 4; i++)
	{
		if (angle == 180 && (main_figure == 2 || main_figure == 3 || main_figure == 5 || main_figure == 4))
		{
			temp[i].x = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * q - 0 + offsetX;
			temp[i].y = (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * q + figures[main_figure][1] / 2 + offsetY;
		}
		else
		{
			temp[i].x = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * q - (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * w + figures[main_figure][1] % 2 + offsetX;
			temp[i].y = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * w + (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * q + figures[main_figure][1] / 2 + offsetY;
		}
		if (!(field[temp[i].x][temp[i].y] == 0 && temp[i].x >= 0 && temp[i].x < 17 && temp[i].y < 26))
			return false;
	}
	return true;
}

bool check_sides_rotate(int main_figure, int offsetX, int offsetY, double angle)
{
	for (int i = 0; i < 4; i++)
	{
		int q = cosl(angle / 180.0 * M_PI);
		int w = sinl(angle / 180.0 * M_PI);
		if (main_figure == 1 && angle == 180)
			angle = 0;
		if (angle == 180 && (main_figure == 2 || main_figure == 3 || main_figure == 5 || main_figure == 4))
		{
			temp[i].x = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * q - 0 + offsetX;
			temp[i].y = (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * q + figures[main_figure][1] / 2 + offsetY;
		}
		else
		{
			temp[i].x = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * q - (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * w + figures[main_figure][1] % 2 + offsetX;
			temp[i].y = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * w + (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * q + figures[main_figure][1] / 2 + offsetY;
		}
		if (!(temp[i].x >= 0 && temp[i].x < 17 && temp[i].y < 26))
			return false;
		if (!(field[temp[i].x][temp[i].y] == 0 && field[temp[i].x][temp[i].y + 1] == 0))
			return false;
	}
	return true;
}

void render_figure(RenderWindow& window, Sprite sprite_figure_main, Sprite sprite_figure_next, Sprite sprite_background, Sprite sprite_save_figure, Text highscore_text, Text score_text, double angle, int main_figure, int next_figure, int offsetX, int offsetY)
{
	window.clear(Color::White);
	window.draw(sprite_background); // ������ ����
	window.draw(score_text);
	window.draw(highscore_text);
	if (main_figure == 1 && angle == 180)
		angle = 0;
	int q = cosl(angle / 180.0 * M_PI);
	int w = sinl(angle / 180.0 * M_PI);
	for (int i = 0; i < 4; i++)
	{
		if (angle == 180 && (main_figure == 2 || main_figure == 3 || main_figure == 5 || main_figure == 4))
		{
			a[i].x = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * q - 0 + offsetX;
			a[i].y = (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * q + figures[main_figure][1] / 2 + offsetY;
		}
		else
		{
			a[i].x = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * q - (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * w + figures[main_figure][1] % 2 + offsetX;
			a[i].y = (figures[main_figure][i] % 2 - figures[main_figure][1] % 2) * w + (figures[main_figure][i] / 2 - figures[main_figure][1] / 2) * q + figures[main_figure][1] / 2 + offsetY;
		}
		b[i].x = figures[next_figure][i] % 2 + 18; // next ������ (����������)
		b[i].y = figures[next_figure][i] / 2 + 1;
		// ������������� ������� ������� ������� ���������
		sprite_figure_main.setPosition(a[i].x * 24, a[i].y * 24);
		sprite_figure_next.setPosition(b[i].x * 24, b[i].y * 24);
		// ��������� �������
		window.draw(sprite_figure_main);
		window.draw(sprite_figure_next);
	}
	fill_field(window, sprite_save_figure); // ���������� ����
	window.draw(score_text);
	window.draw(highscore_text);
	window.display();
}

bool destruction(Text& score_text, Text& highscore_text)
{
	string highscore_str, score_str;
	int k = 0;
	bool check = false;

	for (int j = 0; j < 26; j++)
	{
		k = 0;
		for (int i = 0; i < 17; i++)
		{
			if (field[i][j] != 0)
				k++;
		}
		if (k == 17)
		{
			for (int i = 0; i < 17; i++)
			{
				field[i][j] = 0;
			}
			int j1 = j;
			for (int i = 0; i < 17; i++)
			{
				j = j1;
				while (j != 1)
				{
					swap(field[i][j], field[i][j - 1]);
					j--;
				}
			}
			score += 100;
			if (score > high_score)
			{
				high_score = score;
				score_file();
			}
			check = true;
		}
	}
	score_str = to_string(score);
	highscore_str = to_string(high_score);
	score_text.setString(score_str);
	highscore_text.setString(highscore_str);

	return check;
}

bool game(RenderWindow& window)
{
	Texture texture, background;

	texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/tetromine.jpg");
	background.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/background_game.png");

	Sprite sprite_figure_main(texture), sprite_figure_next(texture), sprite_background(background), sprite_save_figure(texture);

	Font font;
	if (!font.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/blacker.ttf"))
	{
		exit(0);
	}

	Text gameover_text, score_text, highscore_text;
	{
		string highscore_str, score_str;
		score_str = to_string(score);
		highscore_str = to_string(high_score);

		score_text.setFont(font);
		score_text.setString(score_str);
		score_text.setCharacterSize(20);
		score_text.setPosition(435, 142);
		score_text.setFillColor(Color::Green);

		highscore_text.setFont(font);
		highscore_text.setString(highscore_str);
		highscore_text.setCharacterSize(25);
		highscore_text.setPosition(435, 595);
		highscore_text.setFillColor(Color::Red);
	}

	Clock clock;
	Event event;

	int main_figure = rand() % 7;	 // ������ ��� ��������� (���������)
	int color_main = rand() % 4 + 1; // ���� ������ (�������)
	double time_respawn = 2, time_respawn_user = 0.5;
	bool destruction_check = false;

	for (int j = 0; j < 26; j++)
	{
		for (int i = 0; i < 17; i++)
		{
			field[i][j] = 0;
		}
	}

	AudioManager& audioManager = AudioManager::getInstance();

	audioManager.playMusic("game");

	score = 0;

	while (window.isOpen())
	{
		int next_figure = rand() % 7;	 // ������ ��� ��������� (next)
		int color_next = rand() % 4 + 1; // ���� ������ (next)
		int offsetX = rand() % 16;		 // ���� ������ �� X

		sprite_color(sprite_figure_main, color_main);
		sprite_color(sprite_figure_next, color_next);
		double angle = 0;
		int offsetY = -1;

		////////////////////////////////// ����� ����� //////////////////////////////////
		while (true)
		{
			std::this_thread::sleep_for(1ms);
			double time = clock.getElapsedTime().asSeconds();
			clock.restart();
			time_respawn += time;

			///*   ��������� �������   *///

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					audioManager.stopMusic("game");
					if (score > high_score)
					{
						high_score = score;
						score_file();
					}
					write_ini_file();
					window.close();
					return 0;

				case Event::LostFocus:
					audioManager.pauseMusic("game");
					if (menu_pause(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text))
						audioManager.playMusic("game");
					else
						return 0;

				case Event::KeyPressed:
					switch (event.key.code)
					{
					case Keyboard::Left:
						if (offsetX >= 0 && time_respawn_user == 0.5)
						{
							if (main_figure != 0 && offsetX == 0)
								break;
							offsetX--;
							if (!check_sides(main_figure, offsetX, offsetY, angle))
								offsetX++;
							render_figure(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text, angle, main_figure, next_figure, offsetX, offsetY);
						}
						break;
					case Keyboard::Right:
						if (offsetX < 16 && time_respawn_user == 0.5)
						{
							offsetX++;
							if (!check_sides(main_figure, offsetX, offsetY, angle))
								offsetX--;
							render_figure(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text, angle, main_figure, next_figure, offsetX, offsetY);
						}
						break;
					case Keyboard::Down:
						time_respawn_user = 0.033;
						break;
					case Keyboard::Space:
						if (main_figure != 6 && time_respawn_user == 0.5)
						{
							if (angle == 270)
								angle = -90;
							angle += 90;
							if (!check_sides_rotate(main_figure, offsetX, offsetY, angle))
								angle -= 90;
							render_figure(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text, angle, main_figure, next_figure, offsetX, offsetY);
						}
						break;
					case Keyboard::Escape:
						audioManager.pauseMusic("game");
						if (!menu_pause(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text))
							return 0;
						else
							audioManager.playMusic("game");
					}
				}
			}

			if (time_respawn > time_respawn_user)
			{
				offsetY++;

				if (!check_sides(main_figure, offsetX, offsetY, angle))
					break;

				render_figure(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text, angle, main_figure, next_figure, offsetX, offsetY);
				time_respawn = 0;
				time_respawn_user = 0.5;
			}
		}
		///*   �����'���������� ������� ������ �� ���   *///
		{
			audioManager.stopSound("destruction");
			time_respawn = 0;
			window.clear(Color::White);		// �������� ������
			window.draw(sprite_background); // ������ ����
			for (int i = 0; i < 4; i++)
			{
				field[a[i].x][a[i].y] = color_main; // ���������� �������� ������� ����
				sprite_figure_next.setPosition(b[i].x * 24, b[i].y * 24);
				window.draw(sprite_figure_next); // ������ next ������
			}
			// fill_field(window, sprite_save_figure); // ���������� ����
			if (destruction(score_text, highscore_text))
			{
				audioManager.playSound("destruction");
			}
			fill_field(window, sprite_save_figure); // ���������� ����
			window.draw(score_text);
			window.draw(highscore_text);
			destruction_check = false;
			window.display();
		}
		if (gameover())
		{
			audioManager.stopMusic("game");
			audioManager.playSound("gameover");
			menu_restart(window, sprite_figure_main, sprite_figure_next, sprite_background, sprite_save_figure, highscore_text, score_text, font);
			return 0;
		}
		main_figure = next_figure;
		color_main = color_next;
	}
	return 0;
}