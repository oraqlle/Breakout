#include "../headers/MainGameState.h"
#include "../headers/GameEngine.h"

MainGameState MainGameState::m_MainGameState;

void MainGameState::Init(DIM* _dim)
{
	xcon::clear_console();
	dim = _dim;
}

void MainGameState::CleanUp()
{
	xcon::clear_console();
}

void MainGameState::Pause()
{

}

void MainGameState::Resume()
{

}

void MainGameState::HandleEvents(GameEngine* engine)
{
	
}

void MainGameState::Update(GameEngine* engine)
{
	
}

void MainGameState::Draw(GameEngine* engine)
{
	
}