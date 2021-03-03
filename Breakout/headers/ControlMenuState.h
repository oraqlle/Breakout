#pragma once
#include "GameState.h"
#include "GameEngine.h"

class ControlMenuState : public GameState
{
public:
	void Init(DIM* _dim);
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

	DIM* dim;

private:
	static ControlMenuState m_ControlMenuState;
};