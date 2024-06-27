#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>
#include "AudioManager.h"

using namespace std::literals::chrono_literals;
using namespace sf;

extern float mus_vol_menu;
extern float mus_vol_game;
extern float mus_vol_gen;
extern bool music_on;

extern int high_score;
extern int score;

extern bool game(RenderWindow& window, Music& game_music, Music& menu_music, Sound& destruction_sound, Sound& switch_sound, Sound& select_sound, Sound& gameover_sound);
extern void fill_field(RenderWindow& window, Sprite& sprite_save_figure);
extern void write_ini_file();
extern void score_file();

bool menu(RenderWindow& window);
bool menu_pause(RenderWindow& window, Sprite sprite_figure_main, Sprite sprite_figure_next, Sprite sprite_background, Sprite sprite_save_figure, Text highscore_text, Text score_text, Music& game_music, Music& menu_music, Sound& destruction_sound, Sound& switch_sound, Sound& select_sound, Sound& gameover_sound);
bool menu_restart(RenderWindow& window, Sprite sprite_figure_main, Sprite sprite_figure_next, Sprite sprite_background, Sprite sprite_save_figure, Text highscore_text, Text score_text, Font font, Music& game_music, Music& menu_music, Sound& destruction_sound, Sound& switch_sound, Sound& select_sound, Sound& gameover_sound);
bool settings(RenderWindow& window);