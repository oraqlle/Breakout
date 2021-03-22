#pragma once

#include "../include/include.h"

// Move each of these into their respective state header files

struct DIM
{
	int w, h;
};

enum class state_amount;

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
	eStates* state_list;

	~GameEngine();
	void Init(int w, int h);
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