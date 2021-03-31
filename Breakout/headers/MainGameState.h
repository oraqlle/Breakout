#pragma once
#include "GameState.h"

class MainGameState : public GameState
{
public:
	MainGameState() { }
	~MainGameState();
	void Init(GameEngine* engine);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static MainGameState* Instance() {
		return &m_MainGameState;
	}

protected:
	int* p_score;
	int* p_highscore;
	int highscore;
	int text_offset;
	int w, h, s_w, s_h;
	bool init;
	bool border_init;

	core::rectangle<int>* _Border;
	core::rectangle<int>* _Gameboard;
	core::rectangle<int>* _Bricks;
	core::rectangle<int>* _EntryBuff;

	core::posxy* _null;
	core::posxy* g_endline;
	core::posxy* g_midpoint;
	core::posxy* s_midpoint;

	// Entity starting positions
	core::posxy*_PlayerStart;
	core::posxy* _BallStart;
	core::posxy* _StartText;
	core::posxy* _BricksStart;

	// Start Menu & Text Positions
	core::posxy* _Title;
	core::posxy* _ScorePos;

	// File locations
	cstring nTitle;
	cstring nTemp;
	cstring nBaselevel;
	cstring nLevel_1;
	cstring nHighScore;

	core::Matrix<char>* Border;
	core::Matrix<char>* GameBuff;
	core::Matrix<char>* Bricks;
	core::Matrix<char>* EntryBuff;

	Ball* ball;
	Paddle* player;
	

private:
	static MainGameState m_MainGameState;

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

	void Input(GameEngine* engine);
	void Logic(GameEngine* engine);
	void ClearBuffer(core::Matrix<char>* buff, core::rectangle<int>* dim);
	void _Init_Print();
	void PrintGame();
	void PrintGameBoard(core::Matrix<char>* buff);
	void CopyBricks(core::Matrix<char>* buff);

	void PauseMenu();

};