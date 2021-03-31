#include "../headers/GameEngine.h"
#include "../headers/GameState.h"
#include "../headers/MainGameState.h"
#include "../headers/PauseMenuState.h"
#include "../headers/LeaderboardMenuState.h"
#include "../headers/ControlMenuState.h"
#include "../headers/QuitState.h"
#include "../headers/StartMenuState.h"

PauseMenuState PauseMenuState::m_PauseMenuState;

void PauseMenuState::Init(GameEngine* engine)
{
	xcon::clear_console();
	p_score = &g_val->g_score;
	p_highscore = &g_val->g_highscore;
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
			engine->PopState();
		}

		if (current == 'c' || current == 'C')
		{
			engine->PushState(ControlMenuState::Instance());
		}

		if (current == 'v' || current == 'V')
		{
			engine->PushState(LeaderboardMenuState::Instance());
		}

		if (current == 'x' || current == 'X')
		{
			engine->ChangeState(StartMenuState::Instance());
			*p_score = 00;
		}

		if (current == 'q' || current == 'Q')
		{
			engine->ChangeState(QuitState::Instance());
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
	xcon::f_console_print(((engine->game_dim->w / 2) - 4), (engine->game_dim->h / 2), BLUE, "Score: %d", *p_score);

	xcon::console_print(((engine->game_dim->w / 2) - 5), ((engine->game_dim->h / 2) + 1), WHITE, "Resume (E)");
	xcon::console_print(((engine->game_dim->w / 2) - 8), ((engine->game_dim->h / 2) + 2), WHITE, "Controls Menu (C)");
	xcon::console_print(((engine->game_dim->w / 2) - 7), ((engine->game_dim->h / 2) + 3), WHITE, "Leaderboard (V)");
	xcon::console_print(((engine->game_dim->w / 2) - 6), ((engine->game_dim->h / 2) + 4), GREEN, "Save Game (S)");

	xcon::console_print(((engine->game_dim->w / 2) - 14), ((engine->game_dim->h / 2) + 5), YELLOW, "-----------------------------");
	xcon::console_print(((engine->game_dim->w / 2) - 10), ((engine->game_dim->h / 2) + 6), RED, "Quit to Main Menu (X)");
	xcon::console_print(((engine->game_dim->w / 2) - 10), ((engine->game_dim->h / 2) + 7), RED, "Quit Current Game (Q)");
}