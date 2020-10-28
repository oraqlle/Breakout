#pragma once
#include <iostream>
#include <conio.h>
#include <time.h>
#include "ConsoleSettings.h"
#include "Buffer.h"
#include "Ball.h"
#include "Paddle.h"

class GameManager
{
private:
	int width;
	int height;
	int inner_w;
	int inner_h;

	int score;

	char left, right;
	bool quit;

	Ball* ball;
	Paddle* player;

	ConsoleSettings* Console;
	Buffer* mainBuffer;


public:
	GameManager();
	GameManager(int w, int h);
	~GameManager();
private:

	void ScoreUp(Paddle* player);
	void Input();
	void Logic();

public:
	void Run();
};

