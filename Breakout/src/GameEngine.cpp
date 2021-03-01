#include "../headers/GameEngine.h"

void GameEngine::Init()
{
	m_running = true;
}

void GameEngine::CleanUp()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}
}

void GameEngine::ChangeState(GameState* state)
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}


void GameEngine::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void GameEngine::Draw()
{
	// let the state draw the screen
	states.back()->Draw(this);
}