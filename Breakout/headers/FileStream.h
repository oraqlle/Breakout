#pragma 
#include <stdio.h>
#include "defines.h"

class FileStream
{
private:
	FILE* file;
	FILE* fHighScore;

	cstring nHighScore;
	cstring nCurrentSave;
	cstring fLevelName;

public:
	FileStream();
	~FileStream();

	void HighScore(cstring _pname, int& _highscore);
	void OffloadLevel(char input[bufferMAX][bufferMAX]);
	void LoadLevel(cstring _fname, char output[bufferMAX][bufferMAX]);
};

