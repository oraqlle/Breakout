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
	int startX, startY;
	int ballStartX, ballStartY;
	int score;

	char left, right;
	bool quit;
	bool start;

	Ball* ball;
	Paddle* player;

	ConsoleSettings* Console;
	Buffer* mainBuffer;


public:
	GameManager(int w, int h);
	~GameManager();
private:

	void ScoreUp();
	void Input();
	void Start();
	void Logic();

public:
	void Run();
};

