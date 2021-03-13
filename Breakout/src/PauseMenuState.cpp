#include "../headers/PauseMenuState.h"
#include "../headers/GameEngine.h"

PauseMenuState PauseMenuState::m_PauseMenuState;

void PauseMenuState::Init(GameEngine* engine)
{
	xcon::clear_console();
}

void PauseMenuState::CleanUp()
{
	xcon::clear_console();
}

void PauseMenuState::Pause()
{

}

void PauseMenuState::Resume()
{

}

void PauseMenuState::HandleEvents(GameEngine* engine)
{
	if (_kbhit())
	{
		char current = _getch();

		if (current == 'e' || current == 'E')
		{
			pause = false;
			in_game = true;
			border_init = false;
			xcon::clear_console();
		}

		if (current == 'c' || current == 'C')
		{
			pause = false;
			c_menu = true;
			xcon::clear_console();
		}

		if (current == 'v' || current == 'V')
		{
			pause = false;
			l_menu = true;
			xcon::clear_console();
		}

		if (current == 'x' || current == 'X')
		{
			pause = false;
			main_menu = true;
			init = false;
			border_init = false;

			ent->ball->Reset();
			ent->player->Reset();

			score = 0;

			xcon::clear_console();
		}

		if (current == 'q' || current == 'Q')
		{
			pause = false;
			runtime = false;
			xcon::clear_console();
		}
	}
}

void PauseMenuState::Update(GameEngine* engine)
{

}

void PauseMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((engine->game_dim->w / 2) - 3), ((engine->game_dim->h / 2) - 2), YELLOW, "Paused:");
	xcon::console_print(((engine->game_dim->w / 2) - 14), ((engine->game_dim->h / 2) - 1), YELLOW, "-----------------------------");

	//xcon::f_console_print(((_Screen->w / 2) - 4), (_Screen->h / 2), "\033[21;%dm%s\033[0m\n", aBLACK, score);
	xcon::f_console_print(((engine->game_dim->w / 2) - 4), (engine->game_dim->h / 2), BLUE, "Score: %d", score);

	xcon::console_print(((engine->game_dim->w / 2) - 5), ((engine->game_dim->h / 2) + 1), WHITE, "Resume (E)");
	xcon::console_print(((engine->game_dim->w / 2) - 8), ((engine->game_dim->h / 2) + 2), WHITE, "Controls Menu (C)");
	xcon::console_print(((engine->game_dim->w / 2) - 7), ((engine->game_dim->h / 2) + 3), WHITE, "Leaderboard (V)");
	xcon::console_print(((engine->game_dim->w / 2) - 6), ((engine->game_dim->h / 2) + 4), GREEN, "Save Game (S)");

	xcon::console_print(((engine->game_dim->w / 2) - 14), ((engine->game_dim->h / 2) + 5), YELLOW, "-----------------------------");
	xcon::console_print(((engine->game_dim->w / 2) - 10), ((engine->game_dim->h / 2) + 6), RED, "Quit to Main Menu (X)");
	xcon::console_print(((engine->game_dim->w / 2) - 10), ((engine->game_dim->h / 2) + 7), RED, "Quit Current Game (Q)");
}