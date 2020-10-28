#include "ConsoleSettings.h"
#include "Ball.h"
#include "Paddle.h"

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

	Ball* ball;
	Paddle* player;
	ConsoleSettings* Console;

public:
	Buffer(int& _w, int& _h, Ball* _Ball, Paddle* _Player, 
		ConsoleSettings* _Console);
	~Buffer();

	void EmptyFullBuffer();
	void CreateBorder();
	void PrintBorder();
	void PrintGameBuffer();

	void GameBuffer();
	void ClearGameBuffer();
};

