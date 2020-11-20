#include "FileStream.h"

FileStream::FileStream()
	: nHighScore("..\\disc\\highscore.txt"), 
	nCurrentSave("..\\disc\\tempSave.txt") {}

FileStream::~FileStream()
{
	delete file;
}

void FileStream::HighScore(cstring _pname, int& _highscore)
{
	fHighScore = fopen(nHighScore, "a+");
	int temp = fscanf(file, "Name: %s\t\tScore: %d\n", _pname, &_highscore);
	fclose(fHighScore);
}

void FileStream::OffloadLevel(char input[bufferMAX][bufferMAX])
{
	file = fopen(nCurrentSave, "w");

	for (int i = 0; i < bufferMAX; i++)
		for (int j = 0; j < bufferMAX; j++)
			int temp = fputc(input[j][i], file);

	fclose(file);
}

void FileStream::LoadLevel(cstring _fname, char output[bufferMAX][bufferMAX])
{
	file = fopen(_fname, "r");

	for (int i = 0; i < bufferMAX; i++)
		for (int j = 0; j < bufferMAX; j++)
		{
			int z = fgetc(file);
			output[j][i] = (char)z;
		}

	fclose(file);
}