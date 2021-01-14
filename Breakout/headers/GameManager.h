#pragma once
#include "..\include\include.h"
#include <vector>

class GameManager
{
private:
	int score;
	int highscore;

	int s_columns, s_rows;

	bool runtime;
	bool main_menu;
	//bool PressedStart;
	//bool restartKey;
	bool c_menu;
	bool l_menu;
	bool pause;
	bool post_game;
	//bool fromPauseMenu;
	bool quit_game;

	core::rectangle<int>* _Screen;
	core::rectangle<int>* _Border;
	core::rectangle<int>* _Gameboard;
	core::rectangle<int>* _Bricks;

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
	/*FILE* fTitle;
	FILE* fTemp;
	FILE* fBaseLevel;
	FILE* fLevel_1;
	FILE* fHighScore;*/

	//File Names
	cstring nTitle;
	cstring nTemp;
	cstring nBaselevel;
	cstring nLevel_1;
	cstring nHighScore;

	Ball* ball;
	Paddle* player;
	//FileStream* fstream;

	core::Matrix<char>* Screen;
	core::Matrix<char>* Border;
	core::Matrix<char>* GameBuff;
	core::Matrix<char>* Bricks;


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
	//void Pause();

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

	void _Init_();
	void Input();
	void PauseInput();
	void ClearPause();
	void ControlMenu();
	void Logic();

	void MainMenu(colour_t val);
	void ControlsMenu(colour_t val);
	void LeaderboardMenu(colour_t val);
	void PauseMenu(colour_t val);
	void EndScreen(colour_t val);
	void GameWindow(colour_t val);

public:
	void Run();
	void PrintTest();
	void Test();
};

