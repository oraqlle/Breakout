#include "../headers/StartMenuState.h"
#include "../headers/GameEngine.h"

StartMenuState StartMenuState::m_StartMenuState;

void StartMenuState::Init(GameEngine* engine)
{
	xcon::clear_console();
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
			engine->ChangeState(MainGameState::Instance());
			//xcon::clear_console();
		}

		if (current == 'c' || current == 'C')
		{
			engine->PushState(ControlMenuState::Instance());
			//xcon::clear_console();
		}

		if (current == 'v' || current == 'V')
		{
			engine->PushState(LeaderboardMenuState::Instance());
			//xcon::clear_console();
		}

		if (current == 'x' || current == 'X')
		{
			engine->ChangeState(QuitState::Instance());
			//xcon::clear_console();
		}
	}
}

void StartMenuState::Update(GameEngine* engine)
{
	
}

void StartMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((engine->game_dim->w / 2) - 6), (engine->game_dim->h - 10), WHITE, "Start (Space)");
	xcon::console_print(((engine->game_dim->w / 2) - 8), (engine->game_dim->h - 9), WHITE, "Controls Menu (C)");
	xcon::console_print(((engine->game_dim->w / 2) - 7), (engine->game_dim->h - 8), WHITE, "Leaderboard (V)");
	xcon::console_print(((engine->game_dim->w / 2) - 6), (engine->game_dim->h - 7), WHITE, "Quit Game (X)");
}