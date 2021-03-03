#include "../headers/MenuState.h"

MenuState MenuState::m_MenuState;

void MenuState::Init(DIM* _dim)
{
	dim = _dim;
	xcon::clear_console();
}

void MenuState::CleanUp()
{
	xcon::clear_console();
}

void MenuState::Pause()
{
	
}

void MenuState::Resume()
{
	
}

void MenuState::HandleEvents(GameEngine* engine)
{
	
}

void MenuState::Update(GameEngine* game)
{

}

void MenuState::Draw(GameEngine* engine)
{
		
}
