#pragma once
#include <fstream>
#include <stdio.h>


class FileStream
{
private:
	#define MAX 100
	#define cstring const char*

	FILE* file;

public:
	FileStream(cstring _fname, cstring _mode, cstring _pname, int& _highscore);
	FileStream(cstring _fname, cstring _mode, char input[MAX][MAX]);
	~FileStream();
};

