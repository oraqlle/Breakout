#pragma once
#include "GameState.h"
#include "GameEngine.h"

class MenuState : public GameState
{
public:
	void Init(DIM* _dim);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static MenuState* Instance() {
		return &m_MenuState;
	}

protected:
	MenuState() { }
	DIM* dim;

private:
	static MenuState m_MenuState;
};