#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

extern bool menu(RenderWindow&);
extern void read_file();
extern void read_ini_file();

int high_score = 0;
int score = 0;

float mus_vol_menu = 100;
float mus_vol_game = 100;
float mus_vol_gen = 100;
bool music_on = true;