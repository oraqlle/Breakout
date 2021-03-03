#include "../headers/ControlMenuState.h"

ControlMenuState ControlMenuState::m_ControlMenuState;

void ControlMenuState::Init(DIM* _dim)
{
	dim = _dim;
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
			if (prev_screen == MAIN_MENU)
				main_menu = true;
			else if (prev_screen == PAUSE_MENU)
				pause = true;

			c_menu = false;
			prev_screen = CONTROLS_MENU;
			xcon::clear_console();
		}
	}
}

void ControlMenuState::Update(GameEngine* engine)
{
	engine->prev_screen = CONTROL_MENU;
}

void ControlMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((_Screen->w / 2) - 4), (_Screen->h - 18), YELLOW, "Controls:");
	xcon::console_print(((_Screen->w / 2) - 14), (_Screen->h - 17), YELLOW, "-----------------------------");

	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 16), CYAN, "Move Left           (A)");
	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 15), CYAN, "Move Right          (D)");
	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 14), CYAN, "Pause               (E)");
	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 13), CYAN, "Quit Current Game   (Q)");

	xcon::console_print(((_Screen->w / 2) - 14), (_Screen->h - 10), YELLOW, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 5), (_Screen->h - 7), RED, "Return  (X)");
}
