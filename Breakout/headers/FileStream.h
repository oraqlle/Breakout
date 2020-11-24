#pragma 
#include <stdio.h>
#include "BufferStream.h"
#include "defines.h"

class FileStream
{
private:
	BufferStream* Buffer;

public:
	FileStream(
		BufferStream* _Buffer
	);
	~FileStream();

	void HighScore(
		FILE* _fptr, 
		cstring _fname, 
		cstring _pname, 
		int& _highscore
	);

	void OffloadLevel(
		FILE* _fptr, 
		cstring _fname
	);
	
	void LoadLevel(
		FILE* _fptr, 
		cstring _fname, 
		rectangle* _board
	);
};

