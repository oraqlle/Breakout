#pragma once
#include "GameState.h"

class ControlMenuState : public GameState
{
public:
	void Init(GameEngine* engine);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static ControlMenuState* Instance() {
		return &m_ControlMenuState;
	}

protected:
	ControlMenuState() { }

private:
	static ControlMenuState m_ControlMenuState;
};