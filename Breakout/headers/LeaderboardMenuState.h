#pragma once
#include "GameState.h"
#include "GameEngine.h"

class LeaderboardMenuState : public GameState
{
public:
	void Init(GameEngine* engine);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* engine);
	void Update(GameEngine* engine);
	void Draw(GameEngine* engine);

	static LeaderboardMenuState* Instance() {
		return &m_LeaderboardMenuState;
	}

protected:
	LeaderboardMenuState() { }

private:
	static LeaderboardMenuState m_LeaderboardMenuState;
};