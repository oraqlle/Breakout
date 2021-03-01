#include "../headers/MenuState.h"
#include "../headers/GameEngine.h"

MenuState MenuState::m_MenuState;

void MenuState::Init()
{
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

void MenuState::HandleEvents(GameEngine* game)
{
	
}

void MenuState::Update(GameEngine* game)
{

}

void MenuState::Draw(Runtime* RT)
{
	xcon::console_print(((RT->_Screen->w / 2) - 6), (RT->_Screen->h - 10), WHITE, "Start (Space)");
	xcon::console_print(((RT->_Screen->w / 2) - 8), (RT->_Screen->h - 9), WHITE, "Controls Menu (C)");
	xcon::console_print(((RT->_Screen->w / 2) - 7), (RT->_Screen->h - 8), WHITE, "Leaderboard (V)");
	xcon::console_print(((RT->_Screen->w / 2) - 6), (RT->_Screen->h - 7), WHITE, "Quit Game (X)");

	
}
