#pragma once
#include "../include/include.h"

// Move each of these into their respective state header files

struct DIM
{
	int w, h;
};

class GameState;

class GameEngine
{
private:
	bool m_running;
	bool m_resetting;
	int s_columns, s_rows;
	int n_text_offset;

	// the stack of states
	std::vector<GameState*> states;
	core::rectangle<int>* _Screen;
	core::Matrix<char>* Screen;

public:
	DIM* game_dim;
	DIM* screen_dim;
	// temporary solution going to write to a (binary or text ) 
	// file that can be read from any class. 
	int g_score;
	
	~GameEngine();
	void Init(int w = 76, int h = 28);
	void CleanUp();

	void PushState(GameState* state);
	void PopState();
	void ChangeState(GameState* state);
	void Reset();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }
	void Resetting() { m_resetting = false; }
	int TextOffset() { return n_text_offset; }
};