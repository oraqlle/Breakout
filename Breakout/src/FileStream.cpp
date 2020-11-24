#include "..\headers\FileStream.h"

FileStream::FileStream(
	BufferStream* _Buffer
)
{
	Buffer = _Buffer;
}

FileStream::~FileStream()
{
	delete Buffer;
}

void FileStream::HighScore(FILE* _fptr, cstring _fname, cstring _pname, int& _highscore)
{
	#pragma warning(suppress : 4996)
	_fptr = fopen(_fname, "a+");
	int temp = fprintf(_fptr, "Name: %s\t\tScore: %d\n", _pname, _highscore);
	fclose(_fptr);
}

void FileStream::OffloadLevel(FILE* _fptr, cstring _fname)
{
	#pragma warning(suppress : 4996)
	_fptr = fopen(_fname, "w");

	for (int i = 0; i < bufferMAX; i++)
		for (int j = 0; j < bufferMAX; j++)
			int temp = fputc(Buffer->borderBuffer[j][i], _fptr);

	fclose(_fptr);
}

void FileStream::LoadLevel(FILE* _fptr, cstring _fname, rectangle* _board)
{
	#pragma warning(suppress : 4996)
	_fptr = fopen("C:\\Dev\\MyGame\\Breakout\\Breakout\\disc\\title.txt.txt", "r");

	if (_fptr == NULL)
		perror("Error has Occured! File Cannot Be Opened");
	else
		printf("File Opened Successfully!");

	for (int i = 0; i < _board->h; i++)
		for (int j = 0; j < _board->w; j++)
		{
			char temp = fgetc(_fptr);
			Buffer->borderBuffer[j][i] = temp;
		}

	fclose(_fptr);
}