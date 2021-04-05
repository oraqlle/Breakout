#include "../headers/GameEngine.h"
#include "../headers/GameState.h"

// Management Methods
void GameEngine::Init(int w, int h)
{
	// rand() seed
	srand((unsigned int)time(NULL));

	// set the cursors default vis to false
	xcon::set_curser_vis(false);

	// Control booleans
	m_running = true;
	m_resetting = false;

	//Side Text Offset
	n_text_offset = w + 5;

	// Creates a container for the current screen size (windows)
	#ifdef _WIN32
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		s_columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		s_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	#endif

	_Screen = new core::rectangle<int>{ s_columns, s_rows };
	Screen = new core::Matrix<char>(s_columns, s_rows);
	Screen->fill('\x20');

	game_dim = new DIM{ w, h };
	screen_dim = new DIM{ s_columns, s_rows };
	g_vars = new global_vars;
}

GameEngine::~GameEngine()
{
	delete Screen, _Screen;
}

void GameEngine::CleanUp()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}
}

void GameEngine::ChangeState(GameState* state)
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

void GameEngine::Reset()
{

}

void GameEngine::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void GameEngine::Draw()
{
	// let the state draw the screen
	states.back()->Draw(this);
}