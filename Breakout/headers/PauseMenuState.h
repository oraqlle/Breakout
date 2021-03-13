#pragma once
#include "GameState.h"
#include "GameEngine.h"
#include "MainGameState.h"

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
};