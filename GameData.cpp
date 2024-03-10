#include "GameData.h"

void GameData::writeEncryptedData(char* st, ofstream& sc)
{
	int rand_num;
	char rand_char;

	int initial_symbol = 47;
	int last_symbol = 147;

	for (int i = 0; i < strlen(st); i++)
	{
		sc.write((char*)&st[i], sizeof(st[i]));
	}
	for (int i = 0; i < 6; i++)
	{
		rand_num = initial_symbol + (rand() % last_symbol);
		rand_char = rand_num;
		sc.write((char*)&rand_char, sizeof(rand_char));
	}
	sc.write((char*)&file_rozdile, sizeof(file_rozdile));
}

void GameData::shiftScoreCharacters(char* str)
{
	int score_zsuv = 7, tem;
	char temp;
	for (int i = 0; i < strlen(str); i++)
	{
		tem = str[i];
		tem += score_zsuv;
		temp = tem;
		str[i] = temp;
	}
}

void GameData::decryptScoreData(char* st)
{
	high_score = 0;
	char st1[4] = "ONE";
	shiftScoreCharacters(st1);
	char st2[4] = "TWO";
	shiftScoreCharacters(st2);
	char st3[6] = "THREE";
	shiftScoreCharacters(st3);
	char st4[5] = "FOUR";
	shiftScoreCharacters(st4);
	char st5[5] = "FIVE";
	shiftScoreCharacters(st5);
	char st6[4] = "SIX";
	shiftScoreCharacters(st6);
	char st7[6] = "SEVEN";
	shiftScoreCharacters(st7);
	char st8[6] = "EIGHT";
	shiftScoreCharacters(st8);
	char st9[5] = "NINE";
	shiftScoreCharacters(st9);
	char st0[5] = "NULL";
	shiftScoreCharacters(st0);

	char* pch;

	pch = strtok(st, ".");

	while (pch != NULL)
	{
		pch[strlen(pch) - 6] = '\0';

		if (!strcmp(st1, pch))
			high_score = (high_score + 1) * 10;

		else if (!strcmp(st2, pch))
			high_score = (high_score + 2) * 10;

		else if (!strcmp(st3, pch))
			high_score = (high_score + 3) * 10;

		else if (!strcmp(st4, pch))
			high_score = (high_score + 4) * 10;

		else if (!strcmp(st5, pch))
			high_score = (high_score + 5) * 10;

		else if (!strcmp(st6, pch))
			high_score = (high_score + 6) * 10;

		else if (!strcmp(st7, pch))
			high_score = (high_score + 7) * 10;

		else if (!strcmp(st8, pch))
			high_score = (high_score + 8) * 10;

		else if (!strcmp(st9, pch))
			high_score = (high_score + 9) * 10;

		else if (!strcmp(st0, pch))
			high_score = (high_score + 0) * 10;

		pch = strtok(NULL, ".");
	}
	high_score /= 10;
}

void GameData::readData()
{
	string filename = "highscore.dat";
	ifstream out;
	long file_size;
	out.open(filename, ios::binary);
	if (!out.is_open())
		exit(0);
	out.seekg(0, ios::end);
	file_size = out.tellg();
	out.seekg(0);

	char dig[70] = {};
	char temp;

	if (file_size != 0)
	{
		for (int i = 0; i < file_size; i++)
		{
			out.read(&temp, sizeof(char));
			dig[i] = temp;
		}
		decryptScoreData(dig);
	}
	else
		high_score = 0;
	out.close();
}

void GameData::writeData()
{
	string filename = "highscore.dat";
	ofstream sc(filename, ofstream::binary);
	int size = 0;
	int score2 = score;
	int score3 = score;

	while (score2)
	{
		size++;
		score2 /= 10;
	}

	int* score_arr = new int[size];

	for (int i = size - 1; i >= 0; i--)
	{
		score_arr[i] = score3 % 10;
		score3 /= 10;
	}

	for (int i = 0; i < size; i++)
	{
		int dig = score_arr[i];
		char st[6] = "";
		switch (dig)
		{
		case 1:
			strcpy(st, "ONE");
			break;
		case 2:
			strcpy(st, "TWO");
			break;
		case 3:
			strcpy(st, "THREE");
			break;
		case 4:
			strcpy(st, "FOUR");
			break;
		case 5:
			strcpy(st, "FIVE");
			break;
		case 6:
			strcpy(st, "SIX");
			break;
		case 7:
			strcpy(st, "SEVEN");
			break;
		case 8:
			strcpy(st, "EIGHT");
			break;
		case 9:
			strcpy(st, "NINE");
			break;
		case 0:
			strcpy(st, "NULL");
			break;
		}
		shiftScoreCharacters(st);
		writeEncryptedData(st, sc);
	}
	delete[] score_arr;
	sc.close();
}