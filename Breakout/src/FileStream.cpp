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

void FileStream::HighScore(
	FILE* _fptr, 
	cstring _fname, 
	cstring _pname, 
	int& _highscore
)
{
	#pragma warning(suppress : 4996)
	_fptr = fopen(_fname, "a+");
	int temp = fprintf(_fptr, "Name: %s\t\tScore: %d\n", _pname, _highscore);
	fclose(_fptr);
}

void FileStream::OffloadFile(
	FILE* _fptr, 
	cstring _fname
)
{
	#pragma warning(suppress : 4996)
	_fptr = fopen(_fname, "w+");

	for (int i = 0; i < bufferMAX; i++)
		for (int j = 0; j < bufferMAX; j++)
			int temp = fputc(Buffer->borderBuffer[j][i], _fptr);

	fclose(_fptr);
}

int FileStream::LoadFile(
	FILE* _fptr, 
	cstring _fname, 
	rectangle* _dimensions
)
{
	int _size = 0;

	#pragma warning(suppress : 4996)
	_fptr = fopen(_fname, "r");

	#ifndef TESTLOG
	{
		if (_fptr == NULL)
			perror("Error has Occured! File Cannot Be Opened");
		else
		{
			printf("File Opened Successfully!\n");

			for (int i = 0; i < _dimensions->h; i++)
				for (int j = 0; j < _dimensions->w; j++)
				{
					int temp = fgetc(_fptr);
					Buffer->_buffer[j][i] = (char)temp;
					_size++;
				}
		}
	}
	#else
		{
			for (int i = 0; i < _dimensions->h; i++)
				for (int j = 0; j < _dimensions->w; j++)
				{
					int temp = fgetc(_fptr);
					Buffer->_buffer[j][i] = (char)temp;
					_size++;
				}
		}
	#endif /* TESTLOG */



	

	fclose(_fptr);

	return _size;
}