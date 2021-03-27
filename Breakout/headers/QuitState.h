#pragma once
#include "GameState.h"

class QuitState : public GameState
{
public:
	void Init(GameEngine* engine);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static QuitState* Instance() {
		return &m_QuitState;
	}

protected:
	QuitState() { }

private:
	static QuitState m_QuitState;
};