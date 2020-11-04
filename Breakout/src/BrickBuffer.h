#pragma once
#include "ConsoleSettings.h"
#include "Ball.h"
#include "Paddle.h"

class BrickBuffer
{
private:
	int _width, _height;

	const char c_border;

public:
	char brickBuffer[100][100];

	Ball* ball;
	ConsoleSettings* Console;

public:
	BrickBuffer(int& _w, int& _h, char _brick, Ball* _Ball, 
		ConsoleSettings* _Console);
	~BrickBuffer();

	void EmptyFullBuffer();
	void CreateBorder();
	void PrintBorder();
	void PrintGameBuffer();

	void GameBuffer();
	void ClearGameBuffer();
};

