#include "../headers/StartMenuState.h"
#include "../headers/GameEngine.h"

StartMenuState StartMenuState::m_StartMenuState;

void StartMenuState::Init(DIM* _dim)
{
	xcon::clear_console();
	dim = _dim;
}

void StartMenuState::CleanUp()
{
	xcon::clear_console();
}

void StartMenuState::Pause()
{

}

void StartMenuState::Resume()
{

}

void StartMenuState::HandleEvents(GameEngine* engine)
{
	if (_kbhit())
	{
		char current = _getch();

		if (current == '\x20')
		{
			main_menu = false;
			in_game = true;
			xcon::clear_console();
		}

		if (current == 'c' || current == 'C')
		{
			main_menu = false;
			c_menu = true;
			xcon::clear_console();
		}

		if (current == 'v' || current == 'V')
		{
			main_menu = false;
			l_menu = true;
			xcon::clear_console();
		}

		if (current == 'x' || current == 'X')
		{
			main_menu = false;
			runtime = false;
			xcon::clear_console();
		}
	}
}

void StartMenuState::Update(GameEngine* engine)
{
	engine->prev_screen = MAIN_MENU;
}

void StartMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((dim->_Screen->w / 2) - 6), (dim->_Screen->h - 10), WHITE, "Start (Space)");
	xcon::console_print(((dim->_Screen->w / 2) - 8), (dim->_Screen->h - 9), WHITE, "Controls Menu (C)");
	xcon::console_print(((dim->_Screen->w / 2) - 7), (dim->_Screen->h - 8), WHITE, "Leaderboard (V)");
	xcon::console_print(((dim->_Screen->w / 2) - 6), (dim->_Screen->h - 7), WHITE, "Quit Game (X)");
}