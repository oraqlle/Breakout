#pragma once
#include "GameState.h"
#include "GameEngine.h"

class StartMenuState : public GameState
{
public:
	void Init(GameEngine* engine);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static StartMenuState* Instance() {
		return &m_StartMenuState;
	}

protected:
	StartMenuState() { }
	StartMenuState(DIM* _dim);

	DIM* dim;

private:
	static StartMenuState m_StartMenuState;
};