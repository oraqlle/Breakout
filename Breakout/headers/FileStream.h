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

	void writef(
		FILE* _fptr,
		cstring _fname,
		cstring _text
	);

	int readf(
		FILE* _fptr,
		cstring _fname,
		char arr[]
	);

	inline FILE* openf(
		cstring _fname,
		cstring _mode
	);

	inline void closef(
		FILE* _fptr
	);

	void HighScore(
		FILE* _fptr, 
		cstring _fname, 
		cstring _pname, 
		int& _highscore
	);

	void OffloadFile(
		FILE* _fptr, 
		cstring _fname,
		char arr[][BUFFERMAX],
		rectangle* dimensions
	);
	
	int LoadFile(
		FILE* _fptr, 
		cstring _fname, 
		rectangle* _dimensions
	);
};