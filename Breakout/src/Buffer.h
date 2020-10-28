#include "ConsoleSettings.h"

class Buffer
{
private:
	int _width;
	int _height;
	int inner_w;
	int inner_h;

public:
	char mainBuffer[100][100];

	char borderBuffer[100][100];


	ConsoleSettings* Console;

public:
	Buffer(int &_w, int &_h, int posX, int posY, ConsoleSettings* _Console);
	~Buffer();

	void EmptyFullBuffer();
	void CreateBorder();
	void PrintBorder();
	void PrintGameBuffer();

	void GameBuffer();
	void ClearGameBuffer();
};

