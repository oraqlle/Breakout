#pragma once

#include "../include/include.h"


#define NO_SCREEN 0
#define MAIN_MENU 1
#define CONTROLS_MENU 2
#define LEADERBOARD_MENU 3
#define START_SCREEN 4
#define GAME_SCREEN 5
#define PAUSE_MENU 6
#define END_SCREEN 7


class GameEngine
{
private:
	// the stack of states
	std::vector<GameState*> states;

	bool m_running;


private:
	int score;
	int highscore;
	int text_offset;

	int s_columns, s_rows;
	int prev_screen;
	bool init;

	core::rectangle<int>* _Screen;
	core::rectangle<int>* _Border;
	core::rectangle<int>* _Gameboard;
	core::rectangle<int>* _Bricks;

	core::posxy* _null;
	core::posxy* _endline;
	core::posxy* _midpoint;

	core::posxy* _Title;
	core::posxy* _ScorePos;

	core::posxy* _PlayerStart;
	core::posxy* _BallStart;
	core::posxy* _StartText;
	core::posxy* _BricksStart;

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
	GameEngine* engine;

	core::Matrix<char>* Screen;
	core::Matrix<char>* Border;
	core::Matrix<char>* GameBuff;
	core::Matrix<char>* PrevGameBuff;
	core::Matrix<char>* EntryBuff;
	core::Matrix<char>* Bricks;

private:


	void ScoreUp();
	void HighScore(
		int& _score
	);

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
	void CreateBorder();
	void CreateBricks();
	void LoadEntities();

	void Input();
	//void _Init_Input();
	void Logic();
	void ClearBuffer(core::Matrix<char>* buff, core::rectangle<int>* dim);
	//void ClearAll();
	void _Init_Print();
	void PrintGame();
	void PrintGameBoard(core::Matrix<char>* buff);
	void CopyBricks(core::Matrix<char>* buff);

	void MainMenu(colour_t val);
	void ControlsMenu();
	void LeaderboardMenu();
	void PauseMenu();
	void GameWindow();
	void EndScreen();


public:
	void Init(int w, int h);
	void CleanUp();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }
};