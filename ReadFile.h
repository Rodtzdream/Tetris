#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "ini.h"
#include <string>

using namespace std;

extern float mus_vol_menu;
extern float mus_vol_game;
extern float mus_vol_gen;
extern bool music_on;

void writeEncryptedData(char* st, ofstream& sc);
void shiftScoreCharacters(char* str);
void decryptScoreData(char* st);
void readFile();
void writeFile();
void writeIniFile();
void readIniFile();