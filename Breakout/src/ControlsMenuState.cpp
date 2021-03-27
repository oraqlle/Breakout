#include "../headers/GameEngine.h"
#include "../headers/GameState.h"
#include "../headers/ControlMenuState.h"

ControlMenuState ControlMenuState::m_ControlMenuState;

void ControlMenuState::Init(GameEngine* engine)
{
	xcon::clear_console();
}

void ControlMenuState::CleanUp()
{
	xcon::clear_console();
}

void ControlMenuState::Pause()
{
	xcon::clear_console();

}

void ControlMenuState::Resume()
{
	xcon::clear_console();
}

void ControlMenuState::HandleEvents(GameEngine* engine)
{
	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			engine->PopState();
		}
	}
}

void ControlMenuState::Update(GameEngine* engine)
{

}

void ControlMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((engine->game_dim->w / 2) - 4), (engine->game_dim->h - 18), YELLOW, "Controls:");
	xcon::console_print(((engine->game_dim->w / 2) - 14), (engine->game_dim->h - 17), YELLOW, "-----------------------------");

	xcon::console_print(((engine->game_dim->w / 2) - 11), (engine->game_dim->h - 16), CYAN, "Move Left           (A)");
	xcon::console_print(((engine->game_dim->w / 2) - 11), (engine->game_dim->h - 15), CYAN, "Move Right          (D)");
	xcon::console_print(((engine->game_dim->w / 2) - 11), (engine->game_dim->h - 14), CYAN, "Pause               (E)");
	xcon::console_print(((engine->game_dim->w / 2) - 11), (engine->game_dim->h - 13), CYAN, "Quit Current Game   (Q)");

	xcon::console_print(((engine->game_dim->w / 2) - 14), (engine->game_dim->h - 10), YELLOW, "-----------------------------");
	xcon::console_print(((engine->game_dim->w / 2) - 5), (engine->game_dim->h - 7), RED, "Return  (X)");
}
