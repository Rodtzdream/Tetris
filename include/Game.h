#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <math.h>
#include <string>
#include <chrono>
#include <thread>

using namespace sf;

extern int high_score;
extern int score;

extern void write_ini_file();

bool gameover();
void sprite_color(Sprite &sprite, int color);
void fill_field(RenderWindow &window, Sprite &sprite_save_figure);
bool check_sides(int main_figure, int offsetX, int offsetY, double angle);
bool check_sides_rotate(int main_figure, int offsetX, int offsetY, double angle);
void render_figure(RenderWindow &window, Sprite sprite_figure_main, Sprite sprite_figure_next, Sprite sprite_background, Sprite sprite_save_figure, Text high_score_text, Text score_text, double angle, int main_figure, int next_figure, int offsetX, int offsetY);
bool destruction(Text &score_text, Text &highscore_text);
bool game(RenderWindow &window, Music &game_music, Music &menu_music, Sound &destruction_sound, Sound &switch_sound, Sound &select_sound, Sound &gameover_sound);