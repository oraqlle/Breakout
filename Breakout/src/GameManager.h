#pragma once
#include <iostream>
#include <conio.h>
#include <time.h>
#include "ConsoleSettings.h"
#include "Buffer.h"
#include "Ball.h"
#include "Paddle.h"
#include "posxy.h"
#include "rectangle.h"

class GameManager
{
private:
	
	int score;
	int highscore;

	bool quit;
	bool start;
	bool endgame;
	bool pause;
	bool controlMenu;

	rectangle* _Border;
	rectangle* _Gameboard;


	posxy* _ScorePos;
	posxy* _StartPos;
	posxy* _BallStart;

	Ball* ball;
	Paddle* player;
	ConsoleSettings* Console;
	Buffer* mainBuffer;


public:
	GameManager(int w, int h);
	~GameManager();
private:

	
	void ScoreUp();
	void HighScore(int& _score);

	void GameOver();
	void Restart();
	void Restart(const char& _key);
	void Start();
	void Pause();

	void BrickCollision(int& ballX, int& ballY);
	void PaddleCollision(int& ballX, int& ballY, int& playerX, 
		int& playerY);
	void Input();
	void PauseInput();
	void ControlMenu();
	void Logic();

public:
	void Run();
	void PrintTest();
};

