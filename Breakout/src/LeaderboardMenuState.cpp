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

}

void LeaderboardMenuState::Resume()
{

}

void LeaderboardMenuState::HandleEvents(GameEngine* engine)
{
	// code that loads leaderboard from disc
	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			if (engine->prev_screen == MAIN_MENU)
				main_menu = true;
			else if (engine->prev_screen == PAUSE_MENU)
				pause = true;
			else if (engine->prev_screen == END_SCREEN)
				post_game = true;

			l_menu = false;
			xcon::clear_console();
		}
	}
}

void LeaderboardMenuState::Update(GameEngine* engine)
{
	engine->prev_screen = LEADERBOARD_MENU;
}

void LeaderboardMenuState::Draw(GameEngine* engine)
{
	xcon::console_print(((dim->_Screen->w / 2) - 5), (dim->_Screen->h / 2), CYAN, "Leaderboard");
	xcon::console_print(((dim->_Screen->w / 2) - 14), ((dim->_Screen->h / 2) + 1), CYAN, "-----------------------------");
	xcon::console_print(((dim->_Screen->w / 2) - 5), ((dim->_Screen->h / 2) + 2), RED, "Return  (X)");
}