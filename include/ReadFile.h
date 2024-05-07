#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "ini.h"
#include <string.h>

using namespace std;

extern float mus_vol_menu;
extern float mus_vol_game;
extern float mus_vol_gen;
extern bool music_on;

void vrite(char *st, ofstream &sc);
void zsuv_score(char *str);
void decryp(char *st);
void read_file();
void score_file();
void write_ini_file();
void read_ini_file();