#include "../headers/ControlMenuState.h"

ControlMenuState ControlMenuState::m_ControlMenuState;

ControlMenuState::ControlMenuState(DIM* _dim)
{
	dim = _dim;
}

void ControlMenuState::Init()
{
	xcon::clear_console();
}

void ControlMenuState::CleanUp()
{
	xcon::clear_console();
}

void ControlMenuState::Pause()
{

}

void ControlMenuState::Resume()
{

}

void ControlMenuState::HandleEvents(GameEngine* engine)
{
	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			if (engine->prev_screen == MAIN_MENU)
				main_menu = true;
			else if (engine->prev_screen == PAUSE_MENU)
				pause = true;

			c_menu = false;
			engine->prev_screen = CONTROLS_MENU;
			xcon::clear_console();
		}
	}
}

void ControlMenuState::Update(GameEngine* engine)
{
	engine->prev_screen = CONTROLS_MENU;
}

void ControlMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((dim->_Screen->w / 2) - 4), (dim->_Screen->h - 18), YELLOW, "Controls:");
	xcon::console_print(((dim->_Screen->w / 2) - 14), (dim->_Screen->h - 17), YELLOW, "-----------------------------");

	xcon::console_print(((dim->_Screen->w / 2) - 11), (dim->_Screen->h - 16), CYAN, "Move Left           (A)");
	xcon::console_print(((dim->_Screen->w / 2) - 11), (dim->_Screen->h - 15), CYAN, "Move Right          (D)");
	xcon::console_print(((dim->_Screen->w / 2) - 11), (dim->_Screen->h - 14), CYAN, "Pause               (E)");
	xcon::console_print(((dim->_Screen->w / 2) - 11), (dim->_Screen->h - 13), CYAN, "Quit Current Game   (Q)");

	xcon::console_print(((dim->_Screen->w / 2) - 14), (dim->_Screen->h - 10), YELLOW, "-----------------------------");
	xcon::console_print(((dim->_Screen->w / 2) - 5), (dim->_Screen->h - 7), RED, "Return  (X)");
}
