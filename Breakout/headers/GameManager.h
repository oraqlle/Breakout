#pragma once
#include "..\include\include.h"
#include <vector>

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

	core::rectangle<size_t>* _Border;
	core::rectangle<size_t>* _Gameboard;
	core::rectangle<size_t>* _Bricks;

	core::posxy* _null;
	core::posxy* _endline;
	core::posxy* _midpoint;

	core::posxy* _Title;
	core::posxy* _StartText1;

	core::posxy* _ScorePos;
	core::posxy* _StartText2;

	core::posxy* _GameOver;
	core::posxy* _PlayAgain;
	core::posxy* _YesNo;

	core::posxy* _ControlText;
	core::posxy* _Line2;
	core::posxy* _aLeft;
	core::posxy* _dRight;
	core::posxy* _ePause;
	core::posxy* _qQuit;

	core::posxy* _PauseText;
	core::posxy* _Line1;
	core::posxy* _Continue;
	core::posxy* _Restart;
	core::posxy* _Quit;

	core::posxy* _StartPos;
	core::posxy* _BallStart;

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
	core::Matrix<char>* Buffer;
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

