#pragma 
#include <stdio.h>

class FileStream
{
private:
	#define bufferMAX 100
	#define pathMAX 20
	#define cstring const char*

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

