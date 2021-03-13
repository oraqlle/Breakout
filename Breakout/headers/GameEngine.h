#pragma once

#include "../include/include.h"

// Move each of these into their respective state header files

struct DIM
{
	int w, h;
};

class GameEngine
{
private:
	bool m_running;
	int s_columns, s_rows;

	// the stack of states
	std::vector<GameState*> states;
	core::rectangle<int>* _Screen;
	core::Matrix<char>* Screen;

public:
	DIM* game_dim;

private:
	void PushState(GameState* state);
	void PopState();

public:
	~GameEngine();
	void Init(int w, int h);
	void CleanUp();

	void ChangeState(GameState* state);

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }
};