#pragma once
#include "..\include\include.h"

class GameManager
{
private:
	int score;
	int highscore;

	bool run;
	bool InStartMenu;
	bool PressedStart;
	bool restartKey;
	bool endgame;
	bool pause;
	bool fromPauseMenu;
	bool quit;

	rectangle* _Border;
	rectangle* _Gameboard;

	posxy* _null;
	posxy* _endline;
	posxy* _midpoint;

	posxy* _Title;
	posxy* _StartText1;

	posxy* _ScorePos;
	posxy* _StartText2;

	posxy* _GameOver;
	posxy* _PlayAgain;
	posxy* _YesNo;

	posxy* _ControlText;
	posxy* _Line2;
	posxy* _aLeft;
	posxy* _dRight;
	posxy* _ePause;
	posxy* _qQuit;

	posxy* _PauseText;
	posxy* _Line1;
	posxy* _Continue;
	posxy* _Restart;
	posxy* _Quit;

	posxy* _StartPos;
	posxy* _BallStart;

	// File Pointers
	FILE* fTitle;
	FILE* fTemp;
	FILE* fBaseLevel;
	FILE* fLevel_1;
	FILE* fHighScore;

	//File Names
	cstring nTitle;
	cstring nTemp;
	cstring nBaselevel;
	cstring nLevel_1;
	cstring nHighScore;

	Ball* ball;
	Paddle* player;
	ConsoleSettings* Console;
	BufferStream* Buffer;
	FileStream* fstream;


public:
	GameManager(
		int w, 
		int h
	);
	~GameManager();
private:

	
	void ScoreUp();
	void HighScore(
		int& _score
	);

	void StartMenu();

	void GameOver();
	void Restart();
	void Restart(
		const char& _key
	);
	void Start();
	void Pause();

	void BrickCollision(
		int& ballX, 
		int& ballY
	);
	void PaddleCollision(
		int& ballX, 
		int& ballY, 
		int& playerX, 
		int& playerY
	);
	void Input();
	void PauseInput();
	void ClearPause();
	void ControlMenu();
	void Logic();

public:
	void Run();
	void PrintTest();
	void Test();
};

