#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ini.h"
#include <fstream>
#include <string>

using namespace std;

class GameData {
public:
	void readData();
	void writeData();
private:
	void writeEncryptedData(char* st, ofstream& sc);
	void shiftScoreCharacters(char* str);
	void decryptScoreData(char* st);

	int score;
	int high_score;
	const int score_zsuv = 7;
	const char file_rozdile = '.';
};