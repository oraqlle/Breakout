#include "../headers/GameEngine.h"
#include "../headers/GameState.h"
#include "../headers/QuitState.h"
#include "../headers/StartMenuState.h"
#include "../headers/LeaderboardMenuState.h"

QuitState QuitState::m_QuitState;

void QuitState::Init(GameEngine* engine)
{
	xcon::clear_console();
}

void QuitState::CleanUp()
{
	xcon::clear_console();
}

void QuitState::Pause()
{
	xcon::clear_console();

}

void QuitState::Resume()
{
	xcon::clear_console();
}

void QuitState::HandleEvents(GameEngine* engine)
{
	if (_kbhit())
	{
		char current = _getch();

		if (current == '\x20')
		{
			engine->Quit();
		}

		if (current == 'v' || current == 'V')
		{
			engine->PushState(LeaderboardMenuState::Instance());
		}

		if (current == 'x' || current == 'X')
		{
			engine->ChangeState(StartMenuState::Instance());
		}
	}
}

void QuitState::Update(GameEngine* engine)
{

}

void QuitState::Draw(GameEngine* engine)
{
	xcon::console_print((engine->TextOffset() + 9), (engine->game_dim->h - 6), RED, "Game Over!");
	xcon::console_print(engine->TextOffset(), (engine->game_dim->h - 5), YELLOW, "-----------------------------");
	xcon::console_print((engine->TextOffset() + 7), (engine->game_dim->h - 4), CYAN, "Leaderboard (V)");
	xcon::console_print((engine->TextOffset() + 4), (engine->game_dim->h - 3), BLUE, "Quit to Main Menu (X)");
	xcon::console_print((engine->TextOffset() + 6), (engine->game_dim->h - 2), PINK, "Quit Game (Space)");
}