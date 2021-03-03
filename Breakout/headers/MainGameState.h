#pragma once
#include "GameState.h"
#include "GameEngine.h"

class MainGameState : public GameState
{
public:
	void Init(DIM* dim);
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
	MainGameState() { }

	DIM* dim;

private:
	static MainGameState m_MainGameState;
};