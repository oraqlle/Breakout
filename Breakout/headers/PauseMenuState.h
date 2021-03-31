#pragma once
#include "GameState.h"

class PauseMenuState : public GameState
{
public:
	void Init(GameEngine* engine);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static PauseMenuState* Instance() {
		return &m_PauseMenuState;
	}

protected:
	PauseMenuState() { }

private:
	static PauseMenuState m_PauseMenuState;

	int* p_score;
	int* p_highscore;
};