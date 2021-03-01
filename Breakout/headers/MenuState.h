#pragma once
#include "GameState.h"
#include "GameManager.h"

class MenuState : public GameState
{
public:
	void Init();
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(Runtime* RT);

	static MenuState* Instance() {
		return &m_MenuState;
	}

protected:
	MenuState() { }

private:
	static MenuState m_MenuState;
};