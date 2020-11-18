#include "FileStream.h"

FileStream::FileStream(cstring _fname, cstring _mode, cstring _pname, int& _highscore)
{
	file = fopen(_fname, _mode);
	int temp = fscanf(file, "Name: %s\t\tScore: %d\n", _pname, &_highscore);

}

FileStream::FileStream(cstring _fname, cstring _mode, char input[MAX][MAX])
{
	file = fopen(_fname, _mode);

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			int temp = fscanf(file, "%c", &input[j][i]);

	fclose(file);
}

FileStream::~FileStream()
{
	delete file;
}