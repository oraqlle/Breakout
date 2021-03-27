#include "../headers/GameEngine.h"
#include "../headers/GameState.h"
#include "../headers/LeaderboardMenuState.h"

LeaderboardMenuState LeaderboardMenuState::m_LeaderboardMenuState;

void LeaderboardMenuState::Init(GameEngine* engine)
{
	xcon::clear_console();
}

void LeaderboardMenuState::CleanUp()
{
	xcon::clear_console();
}

void LeaderboardMenuState::Pause()
{
	xcon::clear_console();
}

void LeaderboardMenuState::Resume()
{
	xcon::clear_console();
}

void LeaderboardMenuState::HandleEvents(GameEngine* engine)
{
	// code that loads leaderboard from disc
	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			engine->PopState();
			xcon::clear_console();
		}
	}
}

void LeaderboardMenuState::Update(GameEngine* engine)
{

}

void LeaderboardMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((engine->game_dim->w / 2) - 5), (engine->game_dim->h / 2), CYAN, "Leaderboard");
	xcon::console_print(((engine->game_dim->w / 2) - 14), ((engine->game_dim->h / 2) + 1), CYAN, "-----------------------------");
	xcon::console_print(((engine->game_dim->w / 2) - 5), ((engine->game_dim->h / 2) + 2), RED, "Return  (X)");
}