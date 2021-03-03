#include "../headers/GameEngine.h"

// Management Methods
void GameEngine::Init(int w, int h)
{
	// rand() seed
	srand((unsigned int)time(NULL));

	// set the cursors default vis to false
	xcon::set_curser_vis(false);

	// Text offset
	text_offset = w + 5;

	prev_screen = MAIN_MENU;

	// Control booleans
	init = false;
	m_running = true;

	// scores
	score = 00;
	highscore = 00;

	// Creates a container for the current screen size
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	s_columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	s_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	dim._Screen = new core::rectangle<int>{ s_columns, s_rows };


	// Game Sizes
	dim._Border = new core::rectangle<int>{ w, h };
	dim._Gameboard = new core::rectangle<int>{ (w - 3), (h - 2) };
	_Bricks = new core::rectangle<int>{ (w - 5), (h - 19) };

	// Endpoints and Midpoint
	_null = new core::posxy{ 0, 0 };
	_endline = new core::posxy{ 0, (dim._Border->h + 1) };
	_midpoint = new core::posxy{ (w / 2), (h / 2) };

	// Ball and Player Positions
	_PlayerStart = new core::posxy{ ((dim._Gameboard->w / 2) - 13), (dim._Gameboard->h - 3) };
	_BallStart = new core::posxy{ (dim._Gameboard->w / 2), (dim._Gameboard->h - 6) };
	_StartText = new core::posxy{ text_offset, ((dim._Gameboard->h / 2) - 9) };
	_BricksStart = new core::posxy{ 2, 2 };

	// Start Menu Text Positions
	_Title = new core::posxy{ 4, 3 };

	// Text Positions
	_ScorePos = new core::posxy{ text_offset, ((dim._Gameboard->h / 2) - 10) };

	//File Names - "C:\Dev\MyGames\Breakout\Breakout\disc\title.txt"
	nTitle = "./disc/title.txt";
	nTemp = "./disc/temp.txt";
	nBaselevel = "./disc/Base_Layout.txt";
	nLevel_1 = "./disc/Level_1.txt";
	nHighScore = "./disc/HighScore.txt";

	// External Objects
	ball = new Ball(_BallStart);
	player = new Paddle(_PlayerStart);
	//fstream = new FileStream(Buffer);

	Screen = new core::Matrix<char>(100, 100);
	Border = new core::Matrix<char>(w, h);
	GameBuff = new core::Matrix<char>(dim._Gameboard->w, dim._Gameboard->h);
	PrevGameBuff = new core::Matrix<char>(dim._Gameboard->w, dim._Gameboard->h);
	EntryBuff = new core::Matrix<char>(dim._Gameboard->w, dim._Gameboard->h);
	Bricks = new core::Matrix<char>(_Bricks->w, dim._Border->h);
}

GameEngine::~GameEngine()
{
	delete dim._Border, dim._Gameboard, _PlayerStart, _BallStart, _null, _endline,
		_ScorePos, ball, player, Screen, Border, Bricks/*, fstream*/;
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
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
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

// Running Methods

// Score Tracker
void GameEngine::ScoreUp()
{
	score += 10;
	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", score, highscore);
	HighScore(score);
}

// Highscore Tracker
void GameEngine::HighScore(
	int& _score
)
{
	_score > highscore ? highscore = _score : NULL;
}


// Checks Buffer if their are Bricks at the Ball's location
void GameEngine::BrickCollision(
	int& _ballX,
	int& _ballY
)
{
	for (int i = 0; i < _Gameboard->h; i++)
		for (int j = 0; j < _Gameboard->w; j++)
		{
			char _val = GameBuff->get(j, i);
			if ((_val == '#') && (_ballX == j && _ballY == i))
			{
				GameBuff->set(j, i, '\x20');
				Bricks->set(j, i, '\x20');
				ScoreUp();
				ball->randomDir();
			}
		}
}

// Checks if the ball has collided with the paddle
void GameEngine::PaddleCollision(
	int& _ballX,
	int& _ballY,
	int& _playerX,
	int& _playerY
)
{
	for (int i = 0; i < 26; i++)
		if (_ballY == _playerY - 1)
			if (_ballX == _playerX + i)
			{
				core::eDir dir = ball->getDirection();
				switch (dir)
				{
				case core::eDir::DOWNLEFT:
					ball->chanegDir(core::eDir::UPLEFT);
					break;

				case core::eDir::DOWNRIGHT:
					ball->chanegDir(core::eDir::UPRIGHT);
					break;

				case core::eDir::DOWN:
					ball->chanegDir((core::eDir)((rand() % 3) + 1));
					break;

				default:
					break;
				}
			}
}

// User Input
void GameEngine::Input()
{
	ball->Move();

	int BallX = ball->getX();
	int BallY = ball->getY();

	int PlayerX = player->getX();
	int PlayerY = player->getY();


	if (_kbhit())
	{

		while (!init)
		{
			while (_kbhit())
			{
				char current = _getch();

				if ((current == '\x20') && (ball->getDirection() == core::eDir::STOP))
				{
					ball->chanegDir(core::eDir::DOWN);
					ball->Move();
					init = true;
					xcon::console_print(*_StartText, BLACK, "Press 'Space' to Start");

				}
				else
					current = _getch();
			}
		}

		char current = _getch();

		/*while (!init)
		{

			if ((current == '\x20') && (ball->getDirection() == core::eDir::STOP))
			{
				ball->chanegDir(core::eDir::DOWN);
				ball->Move();
				init = true;
				xcon::console_print(*_StartText, BLACK, "Press 'Space' to Start");
			}
		}*/

		if (current == 'a' || current == 'A')
			if (PlayerX > 0)
				player->moveLeft();

		if (current == 'd' || current == 'D')
			if (PlayerX + 26 < _Gameboard->w)
				player->moveRight();

		if (ball->getDirection() == core::eDir::STOP)
		{
			ball->chanegDir(core::eDir::DOWN);
			ball->Move();
		}

		if (current == 'q' || current == 'Q')
		{
			in_game = false;
			post_game = true;
			xcon::clear_console();
		}

		if (current == 'e' || current == 'E')
		{
			pause = true;
			in_game = false;
			xcon::clear_console();
		}
	}

	prev_screen = GAME_SCREEN;
}


// Basic Logic for collisions
void GameEngine::Logic()
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	// Paddle Collison
	PaddleCollision(ballX, ballY, playerX, playerY);

	// Brick Collisions
	BrickCollision(ballX, ballY);

	// Bottom wall collision
	if (ballY == _Gameboard->h)
	{
		in_game = false;
		post_game = true;

		prev_screen = GAME_SCREEN;
	}

	// Top wall collision
	if (ballY == 0)
		ball->chanegDir(ball->getDirection() == core::eDir::UPRIGHT ? core::eDir::DOWNRIGHT : core::eDir::DOWNLEFT);

	// Right wall collision
	if (ballX == _Gameboard->w - 1)
		ball->chanegDir(ball->getDirection() == core::eDir::UPRIGHT ? core::eDir::UPLEFT : core::eDir::DOWNLEFT);

	// Left wall collision
	if (ballX == (_Gameboard->w + 1) - _Gameboard->w)
		ball->chanegDir(ball->getDirection() == core::eDir::UPLEFT ? core::eDir::UPRIGHT : core::eDir::DOWNRIGHT);
}


void GameEngine::CreateBorder()
{
	int temp = Border->fill('\x20');

	for (int column = 0; column < (_Border->w - 1); column++)
	{
		Border->set(column, 0, '\xB2');
	}

	for (int row = 0; row < _Border->h; row++)
	{
		for (int column = 0; column < (_Border->w - 1); column++)
		{
			if (column == 0)
			{
				Border->set(0, row, '\xB2');
			}

			if (column == (_Border->w - 2))
			{
				Border->set(column, row, '\xB2');
				int offset = column + 1;
				Border->set(offset, row, '\n');
			}
		}
	}

	for (int column = 0; column < (_Border->w - 1); column++)
	{
		Border->set(column, (_Border->h - 1), '\xB2');
	}
}


void GameEngine::ClearBuffer(core::Matrix<char>* buff, core::rectangle<int>* _size)
{
	for (int row = 0; row < _size->h; row++)
		for (int column = 0; column < _size->w; column++)
			buff->set(column, row, '\x20');
}


void GameEngine::CreateBricks()
{
	int temp = Bricks->fill('\x20');

	for (int i = 1; i < _Bricks->h; i++)
		for (int j = 2; j < _Bricks->w; j++)
			Bricks->set(j, i, '#');
}


void GameEngine::CopyBricks(core::Matrix<char>* buff)
{
	for (int i = 1; i < _Bricks->h; i++)
		for (int j = 2; j < _Bricks->w; j++)
			if (Bricks->get(j, i) == '#')
				buff->set(j, i, Bricks->get(j, i));
}


void GameEngine::LoadEntities()
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	for (int i = 0; i < _Gameboard->h; i++)
	{
		for (int j = 0; j < _Gameboard->w; j++)
		{
			if (ballX == j && ballY == i)
				GameBuff->set(j, i, 'O');
			else if (GameBuff->get(j, i) == '#')
				continue;
			else
				GameBuff->set(j, i, '\x20');


			for (int Itr = 0; Itr < 26; Itr++)
			{
				if ((j == (playerX + Itr)) && (playerY == i))
					GameBuff->set(j, playerY, '\xDB');
			}
		}
	}
}


void GameEngine::_Init_Print()
{
	if (!border_init)
	{
		xcon::set_curser(*_null);
		int temp1 = Border->print("%c");
		border_init = true;
	}

	CopyBricks(EntryBuff);
	PrintGameBoard(EntryBuff);
	//ClearBuffer(EntryBuff, _Gameboard);

	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", score, highscore);
}


void GameEngine::PrintGameBoard(core::Matrix<char>* buff)
{
	LoadEntities();

	if (!border_init)
	{
		xcon::set_curser(*_null);
		int temp1 = Border->print("%c");
		border_init = true;
	}

	for (int row = 0; row < _Gameboard->h; row++)
	{
		xcon::set_curser(1, (row + 1), false);
		for (int column = 0; column < _Gameboard->w; column++)
		{
			char z = buff->get(column, row);

			if (z == '#')
				xcon::f_console_print(PINK, "%c", z);
			else if (z == 'O')
				xcon::f_console_print(GREEN, "%c", z);
			else
				xcon::f_console_print(WHITE, "%c", z);
		}
	}
}


void GameEngine::PrintGame()
{

	CopyBricks(GameBuff);
	PrintGameBoard(GameBuff);
	//ClearBuffer(GameBuff, _Gameboard);

	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", score, highscore);
}


void GameEngine::GameWindow()
{
	if (!init)
	{
		xcon::console_print(*_StartText, GREEN, "Press 'Space' to Start");
		_Init_Print();
		Input();
		Logic();
	}
	else
	{
		PrintGame();
		Input();
		Logic();
	}
}

void GameEngine::_Init_()
{
	Screen->fill('\x20');
	Border->fill('\x20');
	GameBuff->fill('\x20');
	EntryBuff->fill('\x20');
	Bricks->fill('\x20');


	CreateBorder();
	CreateBricks();
}


void GameEngine::LeaderboardMenu()
{
	// code that loads leaderboard from disc
	xcon::console_print(((_Screen->w / 2) - 5), (_Screen->h / 2), CYAN, "Leaderboard");
	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) + 1), CYAN, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 5), ((_Screen->h / 2) + 2), RED, "Return  (X)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			if (prev_screen == MAIN_MENU)
				main_menu = true;
			else if (prev_screen == PAUSE_MENU)
				pause = true;
			else if (prev_screen == END_SCREEN)
				post_game = true;

			l_menu = false;
			prev_screen = LEADERBOARD_MENU;
			xcon::clear_console();
		}
	}
}


void GameEngine::PauseMenu()
{
	xcon::console_print(((_Screen->w / 2) - 3), ((_Screen->h / 2) - 2), YELLOW, "Paused:");
	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) - 1), YELLOW, "-----------------------------");

	//xcon::f_console_print(((_Screen->w / 2) - 4), (_Screen->h / 2), "\033[21;%dm%s\033[0m\n", aBLACK, score);
	xcon::f_console_print(((_Screen->w / 2) - 4), (_Screen->h / 2), BLUE, "Score: %d", score);

	xcon::console_print(((_Screen->w / 2) - 5), ((_Screen->h / 2) + 1), WHITE, "Resume (E)");
	xcon::console_print(((_Screen->w / 2) - 8), ((_Screen->h / 2) + 2), WHITE, "Controls Menu (C)");
	xcon::console_print(((_Screen->w / 2) - 7), ((_Screen->h / 2) + 3), WHITE, "Leaderboard (V)");
	xcon::console_print(((_Screen->w / 2) - 6), ((_Screen->h / 2) + 4), GREEN, "Save Game (S)");

	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) + 5), YELLOW, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 10), ((_Screen->h / 2) + 6), RED, "Quit to Main Menu (X)");
	xcon::console_print(((_Screen->w / 2) - 10), ((_Screen->h / 2) + 7), RED, "Quit Current Game (Q)");

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

			ball->Reset();
			player->Reset();

			score = 0;

			xcon::clear_console();
		}

		if (current == 'q' || current == 'Q')
		{
			pause = false;
			GameEngine = false;
			xcon::clear_console();
		}
	}

	prev_screen = PAUSE_MENU;
}


void GameEngine::EndScreen()
{
	xcon::console_print((text_offset + 9), (_Gameboard->h - 6), RED, "Game Over!");
	xcon::console_print(text_offset, (_Gameboard->h - 5), YELLOW, "-----------------------------");
	xcon::console_print((text_offset + 7), (_Gameboard->h - 4), CYAN, "Leaderboard (V)");
	xcon::console_print((text_offset + 4), (_Gameboard->h - 3), BLUE, "Quit to Main Menu (X)");
	xcon::console_print((text_offset + 6), (_Gameboard->h - 2), PINK, "Quit Game (Space)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == '\x20')
		{
			GameEngine = false;
			post_game = false;
			xcon::clear_console();
		}

		if (current == 'v' || current == 'V')
		{
			post_game = false;
			l_menu = true;
			xcon::clear_console();
		}

		if (current == 'x' || current == 'X')
		{
			main_menu = true;
			post_game = false;
			init = false;
			border_init = false;

			ball->Reset();
			player->Reset();

			score = 0;

			xcon::clear_console();
		}
	}

	prev_screen = END_SCREEN;
}