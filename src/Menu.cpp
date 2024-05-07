#include "Menu.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

bool menu(RenderWindow &window, Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound)
{
	bool isButton_select = false;

	Texture game_texture, settings_texture, exit_texture, menuBackground_texture, music_square_texture;

	game_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/game.png");
	settings_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/settings.png");
	exit_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/exit.png");
	menuBackground_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/background_menu.jpg");
	if (music_on)
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
	if (!music_on)
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");

	if (music_on)
		on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
	else
		off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);

	Sprite game_sprite(game_texture), settings_sprite(settings_texture), exit_sprite(exit_texture), menuBackground_sprite(menuBackground_texture), music_square_sprite(music_square_texture);

	game_sprite.setPosition(200, 75);
	settings_sprite.setPosition(200, 275);
	exit_sprite.setPosition(200, 475);
	music_square_sprite.setPosition(565, 620);

	window.clear(Color::White);
	window.draw(menuBackground_sprite);
	window.draw(game_sprite);
	window.draw(settings_sprite);
	window.draw(exit_sprite);
	window.draw(music_square_sprite);
	window.display();

	menu_music.play();

	while (window.isOpen())
	{
		std::this_thread::sleep_for(1ms);
		Event event;

		while (window.pollEvent(event))
		{
			std::this_thread::sleep_for(1ms);
			switch (event.type)
			{
			case Event::Closed:
				if (score > high_score)
				{
					high_score = score;
					score_file();
				}
				write_ini_file();
				window.close();
				return 0;

			case Event::LostFocus:
				menu_music.pause();
				switch_sound.setVolume(0);
				break;

			case Event::GainedFocus:
				menu_music.play();
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				else
					off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				break;
			}
			if (IntRect(215, 80, 185, 70).contains(Mouse::getPosition(window)))
			{
				game_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left)) // 1
				{
					select_sound.play();
					menu_music.stop();
					game(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					return 0;
				}
			}
			else if (IntRect(215, 280, 185, 70).contains(Mouse::getPosition(window)))
			{
				settings_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left)) // 2
				{
					select_sound.play();
					menu_music.pause();
					settings_sprite.setColor(Color::White);
					if (!settings(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound))
						return 0;
					menu_music.play();
				}
			}
			else if (IntRect(215, 480, 181, 70).contains(Mouse::getPosition(window)))
			{
				exit_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left)) // 3
				{
					select_sound.play();
					menu_music.stop();
					if (score > high_score)
					{
						high_score = score;
						score_file();
					}
					write_ini_file();
					window.close();
					return 0;
				}
			}
			else if (IntRect(565, 620, 30, 25).contains(Mouse::getPosition(window)))
			{
				music_square_sprite.setColor(Color::Green);
				if (Mouse::isButtonPressed(Mouse::Left)) // 4
				{
					if (music_on)
					{
						music_on = false;
						game_music.setVolume(0);
						menu_music.setVolume(0);
						destruction_sound.setVolume(0);
						switch_sound.setVolume(0);
						select_sound.setVolume(0);
						gameover_sound.setVolume(0);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");
					}
					else
					{
						music_on = true;
						game_music.setVolume(mus_vol_game * (mus_vol_gen / 100));
						menu_music.setVolume(mus_vol_game * (mus_vol_gen / 100));
						destruction_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
						switch_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
						select_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
						gameover_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
					}
				}
			}
			else
			{
				game_sprite.setColor(Color::White);
				settings_sprite.setColor(Color::White);
				exit_sprite.setColor(Color::White);
				music_square_sprite.setColor(Color::White);
				switch_sound.stop();
				isButton_select = false;
			}
			window.clear(Color::White);
			window.draw(menuBackground_sprite);
			window.draw(game_sprite);
			window.draw(settings_sprite);
			window.draw(exit_sprite);
			window.draw(music_square_sprite);
			window.display();
		}
	}
	return 0;
}

bool menu_pause(RenderWindow &window, Sprite sprite_figure_main, Sprite sprite_figure_next, Sprite sprite_background, Sprite sprite_save_figure, Text highscore_text, Text score_text, Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound)
{
	bool isButton_select = false;

	Texture resume_texture, restart_texture, settings_texture, main_menu_texture, music_square_texture;

	resume_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/resume.png");
	restart_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/restart.png");
	settings_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/settings.png");
	main_menu_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/main_menu.png");

	if (music_on)
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
	else
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");

	Sprite resume_sprite(resume_texture), restart_sprite(restart_texture), settings_sprite(settings_texture), main_menu_sprite(main_menu_texture), music_square_sprite(music_square_texture);

	resume_sprite.setPosition(200, 100);
	restart_sprite.setPosition(200, 200);
	settings_sprite.setPosition(200, 340);
	main_menu_sprite.setPosition(200, 400);
	music_square_sprite.setPosition(565, 620);

	window.clear(Color::White);				// �������� ������
	window.draw(sprite_background);			// ������ ����
	fill_field(window, sprite_save_figure); // ���������� ����
	window.draw(score_text);
	window.draw(highscore_text);
	window.draw(resume_sprite);
	window.draw(restart_sprite);
	window.draw(main_menu_sprite);
	window.draw(settings_sprite);
	window.draw(music_square_sprite);
	window.display();

	while (window.isOpen())
	{
		std::this_thread::sleep_for(1ms);
		Event event;

		while (window.pollEvent(event))
		{
			std::this_thread::sleep_for(1ms);
			switch (event.type)
			{
			case Event::Closed:
				if (score > high_score)
				{
					high_score = score;
					score_file();
				}
				write_ini_file();
				window.close();
				return false;

			case Event::LostFocus:
				switch_sound.setVolume(0);
				break;

			case Event::GainedFocus:
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				else
					off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					return true;
				}
			}
			if (IntRect(200, 140, 200, 68).contains(Mouse::getPosition(window)))
			{
				resume_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					return true;
				}
			}
			else if (IntRect(200, 240, 200, 68).contains(Mouse::getPosition(window)))
			{
				restart_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					game_music.stop();
					game(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					return false;
				}
			}
			else if (IntRect(200, 342, 200, 68).contains(Mouse::getPosition(window)))
			{
				settings_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					game_music.pause();
					settings_sprite.setColor(Color::White);
					if (!settings(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound))
						return false;
					if (music_on)
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
					else
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");
				}
			}
			else if (IntRect(200, 440, 200, 68).contains(Mouse::getPosition(window)))
			{
				main_menu_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					game_music.stop();
					menu_music.stop();
					menu(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					return false;
				}
			}
			else if (IntRect(565, 620, 30, 25).contains(Mouse::getPosition(window)))
			{
				music_square_sprite.setColor(Color::Green);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					isButton_select = true;
					if (music_on)
					{
						music_on = false;
						off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");
					}
					else
					{
						music_on = true;
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
					}
					break;
				}
			}
			else
			{
				resume_sprite.setColor(Color::White);
				restart_sprite.setColor(Color::White);
				main_menu_sprite.setColor(Color::White);
				settings_sprite.setColor(Color::White);
				music_square_sprite.setColor(Color::White);
				switch_sound.stop();
				isButton_select = false;
			}
			window.clear(Color::White);
			window.draw(sprite_background);			// ������ ����
			fill_field(window, sprite_save_figure); // ���������� ����
			window.draw(score_text);
			window.draw(highscore_text);
			window.draw(resume_sprite);
			window.draw(restart_sprite);
			window.draw(main_menu_sprite);
			window.draw(settings_sprite);
			window.draw(music_square_sprite);
			window.display();
		}
	}
}

bool menu_restart(RenderWindow &window, Sprite sprite_figure_main, Sprite sprite_figure_next, Sprite sprite_background, Sprite sprite_save_figure, Text highscore_text, Text score_text, Font font, Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound)
{
	gameover_sound.play();

	bool isButton_select = false;

	Texture restart_texture, settings_texture, main_menu_texture, music_square_texture;
	restart_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/restart.png");
	settings_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/settings.png");
	main_menu_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/main_menu.png");

	if (music_on)
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
	else
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");

	Sprite restart_sprite(restart_texture), settings_sprite(settings_texture), main_menu_sprite(main_menu_texture), music_square_sprite(music_square_texture);
	restart_sprite.setPosition(200, 150);
	settings_sprite.setPosition(200, 310);
	main_menu_sprite.setPosition(200, 395);
	music_square_sprite.setPosition(565, 620);

	Text gameover_text;
	gameover_text.setFont(font);
	gameover_text.setString(" Game Over ");
	gameover_text.setCharacterSize(64);
	gameover_text.setPosition(115, 75);
	gameover_text.setFillColor(Color::Black);

	window.clear(Color::White);				// �������� ������
	window.draw(sprite_background);			// ������ ����
	fill_field(window, sprite_save_figure); // ���������� ����
	window.draw(score_text);
	window.draw(highscore_text);
	window.draw(restart_sprite);
	window.draw(settings_sprite);
	window.draw(main_menu_sprite);
	window.draw(gameover_text);
	window.draw(music_square_sprite);
	window.display();

	while (window.isOpen())
	{
		std::this_thread::sleep_for(1ms);
		Event event;

		while (window.pollEvent(event))
		{
			std::this_thread::sleep_for(1ms);
			switch (event.type)
			{
			case Event::Closed:
				if (score > high_score)
				{
					high_score = score;
					score_file();
				}
				write_ini_file();
				window.close();
				return false;

			case Event::LostFocus:
				switch_sound.setVolume(0);
				break;

			case Event::GainedFocus:
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				else
					off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					menu(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					return 0;
				}
			}
			if (IntRect(200, 190, 200, 70).contains(Mouse::getPosition(window)))
			{
				restart_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					game_music.stop();
					game(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					return true;
				}
			}
			else if (IntRect(200, 311, 200, 70).contains(Mouse::getPosition(window)))
			{
				settings_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left)) // 2
				{
					select_sound.play();
					menu_music.pause();
					settings_sprite.setColor(Color::White);
					if (!settings(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound))
						return 0;
				}
			}
			else if (IntRect(200, 435, 200, 70).contains(Mouse::getPosition(window)))
			{
				main_menu_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					game_music.stop();
					menu_music.stop();
					menu(window, game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					return false;
				}
			}
			else if (IntRect(565, 620, 30, 25).contains(Mouse::getPosition(window)))
			{
				music_square_sprite.setColor(Color::Green);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					isButton_select = true;
					if (music_on)
					{
						music_on = false;
						off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");
					}
					else
					{
						music_on = true;
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
					}
					break;
				}
			}
			else
			{
				restart_sprite.setColor(Color::White);
				settings_sprite.setColor(Color::White);
				main_menu_sprite.setColor(Color::White);
				music_square_sprite.setColor(Color::White);
				isButton_select = false;
				switch_sound.stop();
			}
			window.clear(Color::White);
			window.draw(sprite_background);			// ������ ����
			fill_field(window, sprite_save_figure); // ���������� ����
			window.draw(score_text);
			window.draw(highscore_text);
			window.draw(restart_sprite);
			window.draw(main_menu_sprite);
			window.draw(settings_sprite);
			window.draw(gameover_text);
			window.draw(music_square_sprite);
			window.display();
		}
	}
}

bool settings(RenderWindow &window, Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound)
{
	int menuNum = 0;
	bool isButton_select = false;

	Font font;
	if (!font.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/blacker.ttf"))
	{
		exit(0);
	}

	menu_music.play();

	Texture mus_menu_tex, plus_tex, minus_tex, mus_game_tex, but_back_tex, mus_gen_tex, background_texture, mixer_field_texture, mixer_texture, music_square_texture;

	background_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/background_menu.jpg");

	mus_gen_tex.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/general_sound.png");
	mus_game_tex.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/music.png");
	mus_menu_tex.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/sound.png");
	but_back_tex.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/back.png");

	plus_tex.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/plus.png");
	minus_tex.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/minus.png");

	mixer_field_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/mixer_field.png");
	mixer_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/mixer.png");

	if (music_on)
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
	if (!music_on)
		music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");

	Sprite mus_menu_sprite(mus_menu_tex), plus_menu_sprite(plus_tex), minus_menu_sprite(minus_tex), mixer_field_menu_sprite(mixer_field_texture), mixer_menu_sprite(mixer_texture);
	Sprite mus_game_sprite(mus_game_tex), plus_game_sprite(plus_tex), minus_game_sprite(minus_tex), mixer_field_game_sprite(mixer_field_texture), mixer_game_sprite(mixer_texture);
	Sprite mus_gen_sprite(mus_gen_tex), plus_gen_sprite(plus_tex), minus_gen_sprite(minus_tex), mixer_field_gen_sprite(mixer_field_texture), mixer_gen_sprite(mixer_texture);
	Sprite but_back_sprite(but_back_tex), music_square_sprite(music_square_texture), background_sprite(background_texture);

	but_back_sprite.setPosition(205, 550);

	mus_gen_sprite.setPosition(200, 15);
	mixer_field_gen_sprite.setPosition(194, 151);
	mixer_gen_sprite.setPosition(2 * mus_vol_gen + 197, 150);
	plus_gen_sprite.setPosition(352, 105);
	minus_gen_sprite.setPosition(60, 105);

	mus_menu_sprite.setPosition(200, 160);
	mixer_field_menu_sprite.setPosition(194, 296);
	mixer_menu_sprite.setPosition(2 * mus_vol_menu + 197, 295);
	plus_menu_sprite.setPosition(352, 250);
	minus_menu_sprite.setPosition(60, 250);

	mus_game_sprite.setPosition(200, 305);
	mixer_field_game_sprite.setPosition(194, 441);
	mixer_game_sprite.setPosition(2 * mus_vol_game + 197, 440);
	plus_game_sprite.setPosition(352, 395);
	minus_game_sprite.setPosition(60, 395);

	music_square_sprite.setPosition(565, 620);

	Text mus_menu_vol_text, mus_game_vol_text, mus_gen_vol_text;

	mus_gen_vol_text.setCharacterSize(15);
	mus_gen_vol_text.setPosition(291, 36);
	mus_gen_vol_text.setFillColor(Color::Black);
	mus_gen_vol_text.setFont(font);

	mus_menu_vol_text.setCharacterSize(15);
	mus_menu_vol_text.setPosition(291, 181);
	mus_menu_vol_text.setFillColor(Color::Black);
	mus_menu_vol_text.setFont(font);

	mus_game_vol_text.setCharacterSize(15);
	mus_game_vol_text.setPosition(291, 326);
	mus_game_vol_text.setFillColor(Color::Black);
	mus_game_vol_text.setFont(font);

	if (mus_vol_gen < 0)
		mus_vol_gen = 0;
	else if (mus_vol_gen > 100)
		mus_vol_gen = 100;

	else if (mus_vol_menu < 0)
		mus_vol_menu = 0;
	else if (mus_vol_menu > 100)
		mus_vol_menu = 100;

	else if (mus_vol_game < 0)
		mus_vol_game = 0;
	else if (mus_vol_game > 100)
		mus_vol_game = 100;

	int mus_vol_int = int(mus_vol_gen);
	mus_gen_vol_text.setString(std::to_string(mus_vol_int));
	mus_vol_int = int(mus_vol_menu);
	mus_menu_vol_text.setString(std::to_string(mus_vol_int));
	mus_vol_int = int(mus_vol_game);
	mus_game_vol_text.setString(std::to_string(mus_vol_int));

	window.clear(Color::White);
	window.draw(background_sprite);
	window.draw(but_back_sprite);
	window.draw(music_square_sprite);

	window.draw(mus_menu_sprite);
	window.draw(plus_menu_sprite);
	window.draw(minus_menu_sprite);
	window.draw(mus_menu_vol_text);
	window.draw(mixer_field_menu_sprite);
	window.draw(mixer_menu_sprite);

	window.draw(mus_game_sprite);
	window.draw(plus_game_sprite);
	window.draw(minus_game_sprite);
	window.draw(mus_game_vol_text);
	window.draw(mixer_field_game_sprite);
	window.draw(mixer_game_sprite);

	window.draw(mus_gen_sprite);
	window.draw(plus_gen_sprite);
	window.draw(minus_gen_sprite);
	window.draw(mus_gen_vol_text);
	window.draw(mixer_field_gen_sprite);
	window.draw(mixer_gen_sprite);

	window.display();

	Event event;

	while (window.isOpen())
	{
		std::this_thread::sleep_for(1ms);

		while (window.pollEvent(event))
		{
			std::this_thread::sleep_for(1ms);
			switch (event.type)
			{
			case Event::Closed:
				if (score > high_score)
				{
					high_score = score;
					score_file();
				}
				write_ini_file();
				window.close();
				return 0;

			case Event::LostFocus:
				menu_music.pause();
				switch_sound.setVolume(0);
				break;

			case Event::GainedFocus:
				menu_music.play();
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				else
					off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					menu_music.stop();
					return true;
				}
			}

			if (event.mouseMove.y >= 140 && event.mouseMove.y <= 182 && event.mouseMove.x >= 197 && event.mouseMove.x <= 397 && Mouse::isButtonPressed(Mouse::Left))
			{
				mixer_gen_sprite.setPosition(event.mouseMove.x, 150);
				mus_vol_gen = (event.mouseMove.x - 197) / 2;
				if (mus_vol_gen == 100)
					mus_gen_vol_text.setPosition(285, 36);
				else if (mus_vol_gen == 0)
					mus_gen_vol_text.setPosition(293, 36);
				else
					mus_gen_vol_text.setPosition(291, 36);
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
			}
			else if (event.mouseMove.y >= 285 && event.mouseMove.y <= 327 && event.mouseMove.x >= 197 && event.mouseMove.x <= 397 && Mouse::isButtonPressed(Mouse::Left))
			{
				mixer_menu_sprite.setPosition(event.mouseMove.x, 295);
				mus_vol_menu = (event.mouseMove.x - 197) / 2;
				if (mus_vol_menu == 100)
					mus_menu_vol_text.setPosition(285, 181);
				else if (mus_vol_menu == 0)
					mus_menu_vol_text.setPosition(293, 181);
				else
					mus_menu_vol_text.setPosition(291, 181);
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
			}
			else if (event.mouseMove.y >= 430 && event.mouseMove.y <= 472 && event.mouseMove.x >= 197 && event.mouseMove.x <= 397 && Mouse::isButtonPressed(Mouse::Left))
			{
				mixer_game_sprite.setPosition(event.mouseMove.x, 440);
				mus_vol_game = (event.mouseMove.x - 197) / 2;
				if (mus_vol_game == 100)
					mus_game_vol_text.setPosition(285, 326);
				else if (mus_vol_game == 0)
					mus_game_vol_text.setPosition(293, 326);
				else
					mus_game_vol_text.setPosition(291, 326);
				if (music_on)
					on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
			}

			else if (IntRect(416, 131, 56, 56).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
			{
				plus_gen_sprite.setColor(Color::Green);
				if (!isButton_select)
				{
					isButton_select = true;
					mus_vol_gen += 5;
					if (mus_vol_gen > 100)
						mus_vol_gen = 100;
					if (mus_vol_gen == 100)
						mus_gen_vol_text.setPosition(285, 36);
					else
						mus_gen_vol_text.setPosition(291, 36);
					if (music_on)
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					break;
				}
			}
			else if (IntRect(123, 151, 58, 22).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
			{
				minus_gen_sprite.setColor(Color::Green);
				if (!isButton_select)
				{
					isButton_select = true;
					mus_vol_gen -= 5;
					if (mus_vol_gen < 0)
						mus_vol_gen = 0;
					if (mus_vol_gen == 0)
						mus_gen_vol_text.setPosition(293, 36);
					else
						mus_gen_vol_text.setPosition(291, 36);
					if (music_on)
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					break;
				}
			}
			else if (IntRect(416, 276, 56, 56).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
			{
				plus_menu_sprite.setColor(Color::Green);
				if (!isButton_select)
				{
					isButton_select = true;
					mus_vol_menu += 5;
					if (mus_vol_menu > 100)
						mus_vol_menu = 100;
					if (mus_vol_menu == 100)
						mus_menu_vol_text.setPosition(285, 181);
					else
						mus_menu_vol_text.setPosition(291, 181);
					if (music_on)
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					break;
				}
			}
			else if (IntRect(123, 296, 58, 22).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
			{
				minus_menu_sprite.setColor(Color::Green);
				if (!isButton_select)
				{
					isButton_select = true;
					mus_vol_menu -= 5;
					if (mus_vol_menu < 0)
						mus_vol_menu = 0;
					if (mus_vol_menu == 0)
						mus_menu_vol_text.setPosition(293, 181);
					else
						mus_menu_vol_text.setPosition(291, 181);
					if (music_on)
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					break;
				}
			}
			else if (IntRect(416, 421, 56, 56).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
			{
				plus_game_sprite.setColor(Color::Green);
				if (!isButton_select)
				{
					isButton_select = true;
					mus_vol_game += 5;
					if (mus_vol_game > 100)
						mus_vol_game = 100;
					if (mus_vol_game == 100)
						mus_game_vol_text.setPosition(285, 326);
					else
						mus_game_vol_text.setPosition(291, 326);
					if (music_on)
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					break;
				}
			}
			else if (IntRect(123, 441, 58, 22).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
			{
				minus_game_sprite.setColor(Color::Green);
				if (!isButton_select)
				{
					isButton_select = true;
					mus_vol_game -= 5;
					if (mus_vol_game < 0)
						mus_vol_game = 0;
					if (mus_vol_game == 0)
						mus_game_vol_text.setPosition(293, 326);
					else
						mus_game_vol_text.setPosition(291, 326);
					if (music_on)
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
					break;
				}
			}
			else if (IntRect(207, 558, 181, 74).contains(Mouse::getPosition(window)))
			{
				but_back_sprite.setColor(Color::Green);
				if (!isButton_select)
					switch_sound.play();
				isButton_select = true;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					select_sound.play();
					menu_music.pause();
					return 1;
				}
			}
			else if (IntRect(565, 620, 30, 25).contains(Mouse::getPosition(window)))
			{
				music_square_sprite.setColor(Color::Green);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					isButton_select = true;
					if (music_on)
					{
						music_on = false;
						off_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/novolume.png");
					}
					else
					{
						music_on = true;
						on_music(game_music, menu_music, destruction_sound, switch_sound, select_sound, gameover_sound);
						music_square_texture.loadFromFile(std::string(XSTRING(SOURCE_ROOT)) + "/resources/volume.png");
					}
					break;
				}
			}
			else
			{
				plus_menu_sprite.setColor(Color::White);
				minus_menu_sprite.setColor(Color::White);
				plus_game_sprite.setColor(Color::White);
				minus_game_sprite.setColor(Color::White);
				plus_gen_sprite.setColor(Color::White);
				minus_gen_sprite.setColor(Color::White);
				but_back_sprite.setColor(Color::White);
				music_square_sprite.setColor(Color::White);
				isButton_select = false;
				menuNum = 0;
			}

			mixer_gen_sprite.setPosition(2 * mus_vol_gen + 197, 150);
			mixer_menu_sprite.setPosition(2 * mus_vol_menu + 197, 295);
			mixer_game_sprite.setPosition(2 * mus_vol_game + 197, 440);

			int mus_vol_int = int(mus_vol_gen);
			mus_gen_vol_text.setString(std::to_string(mus_vol_int));
			mus_vol_int = int(mus_vol_menu);
			mus_menu_vol_text.setString(std::to_string(mus_vol_int));
			mus_vol_int = int(mus_vol_game);
			mus_game_vol_text.setString(std::to_string(mus_vol_int));
		}

		window.clear(Color::White);
		window.draw(background_sprite);
		window.draw(but_back_sprite);
		window.draw(music_square_sprite);

		window.draw(mus_menu_sprite);
		window.draw(plus_menu_sprite);
		window.draw(minus_menu_sprite);
		window.draw(mus_menu_vol_text);
		window.draw(mixer_field_menu_sprite);
		window.draw(mixer_menu_sprite);

		window.draw(mus_game_sprite);
		window.draw(plus_game_sprite);
		window.draw(minus_game_sprite);
		window.draw(mus_game_vol_text);
		window.draw(mixer_field_game_sprite);
		window.draw(mixer_game_sprite);

		window.draw(mus_gen_sprite);
		window.draw(plus_gen_sprite);
		window.draw(minus_gen_sprite);
		window.draw(mus_gen_vol_text);
		window.draw(mixer_field_gen_sprite);
		window.draw(mixer_gen_sprite);

		window.display();
	}
	return 0;
}

void on_music(Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound)
{
	game_music.setVolume(mus_vol_game * (mus_vol_gen / 100));
	menu_music.setVolume(mus_vol_game * (mus_vol_gen / 100));
	destruction_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
	switch_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
	select_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
	gameover_sound.setVolume(mus_vol_menu * (mus_vol_gen / 100));
}

void off_music(Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound)
{
	game_music.setVolume(0);
	menu_music.setVolume(0);
	destruction_sound.setVolume(0);
	switch_sound.setVolume(0);
	select_sound.setVolume(0);
	gameover_sound.setVolume(0);
}