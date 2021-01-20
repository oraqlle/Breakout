#include "..\headers\GameManager.h"

GameManager::GameManager(
	int w, 
	int h
)
{
	// rand() seed
	srand((unsigned int)time(NULL));

	// set the cursors default vis to false
	xcon::set_curser_vis(false);

	// Text offset
	const int oset = w + 5;

	// Control booleans
	init = false;
	border_init = false;

	runtime = true;
	main_menu = true;
	//PressedStart;
	//restartKey;
	c_menu = false;
	l_menu = false;
	pause = false;
	post_game = false;
	//fromPauseMenu;
	quit_game = true;
	
	// scores
	score = 00;
	highscore = 00;

	// Creates a container for the current screen size
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	s_columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	s_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	_Screen = new core::rectangle<int>{ s_columns, s_rows };


	// Game Sizes
	_Border = new core::rectangle<int>{ w, h };
	_Gameboard = new core::rectangle<int>{ (w - 3), (h - 2) };
	_Bricks = new core::rectangle<int>{ (w - 5), (h - 19) };
	
	// Endpoints and Midpoint
	_null = new core::posxy{ 0, 0 };
	_endline = new core::posxy{ 0, (_Border->h + 1) };
	_midpoint = new core::posxy{ (w / 2), (h / 2) };

	// Ball and Player Positions
	_PlayerStart = new core::posxy{ ((_Gameboard->w / 2) - 13), (_Gameboard->h - 3) };
	_BallStart = new core::posxy{ (_Gameboard->w / 2), (_Gameboard->h - 6) };
	_StartText = new core::posxy{ oset, (h - 23) };
	_BricksStart = new core::posxy{ 2, 2 };

	// Start Menu Text Positions
	_Title = new core::posxy{ 4, 3 };

	// Text Positions
	_ScorePos = new core::posxy{ oset, (h - 24) };

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
	GameBuff = new core::Matrix<char>( _Gameboard->w, _Gameboard->h);
	PrevGameBuff = new core::Matrix<char>( _Gameboard->w, _Gameboard->h);
	EntryBuff = new core::Matrix<char>( _Gameboard->w, _Gameboard->h);
	Bricks = new core::Matrix<char>(_Bricks->w, _Border->h);
}

// Destructor
GameManager::~GameManager()
{
	delete _Border, _Gameboard, _PlayerStart, _BallStart, _null, _endline,
		_ScorePos, ball, player, Screen, Border, Bricks/*, fstream*/;
}

// Score Tracker
void GameManager::ScoreUp()
{
	score += 10;
	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", score, highscore);
	HighScore(score);
}

// Highscore Tracker
void GameManager::HighScore(
	int& _score
)
{
	_score > highscore ? highscore = _score : NULL;
}

// Runs when the player loses or quits
//void GameManager::GameOver()
//{
//	//Buffer->PrintGameBuffer();
//
//	xcon::console_print(*_GameOver, RED, "Game Over!");
//
//	xcon::console_print(*_PlayAgain, GREEN, "Play Again");
//
//	xcon::console_print(*_YesNo, WHITE, "[Y/N]: ");
//
//	char playAgain;
//	#pragma warning(suppress : 4996)
//	int temp = scanf("%c", &playAgain);
//
//	//Restart(playAgain);
//}


// Checks Buffer if their are Bricks at the Ball's location
void GameManager::BrickCollision(
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
				ScoreUp();
				ball->randomDir();
			}
		}
}

// Checks if the ball has collided with the paddle
void GameManager::PaddleCollision(
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
void GameManager::Input()
{
	ball->Move();

	int BallX = ball->getX();
	int BallY = ball->getY();

	int PlayerX = player->getX();
	int PlayerY = player->getY();

	if (_kbhit())
	{
		char current = _getch();

		while (!init)
			if ((current == '\x20') && (ball->getDirection() == core::eDir::STOP))
			{
				ball->chanegDir(core::eDir::DOWN);
				ball->Move();
				init = true;
				xcon::console_print(*_StartText, BLACK, "Press 'Space' to Start");
			}

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
			quit_game = true;
			post_game = true;
			xcon::clear_console();
		}

		if (current == 'e' || current == 'E')
		{
			pause = true;
			quit_game = true;
			xcon::clear_console();
		}
	}
}


// Basic Logic for collisions
void GameManager::Logic()
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
		quit_game = true;

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


void GameManager::CreateBorder()
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


void GameManager::ClearBuffer(core::Matrix<char>* buff, core::rectangle<int>* dim)
{
	for (int row = 0; row < dim->h; row++)
		for (int column = 0; column < dim->w; column++)
			buff->set(column, row, '\x20');
}


void GameManager::CreateBricks()
{
	int temp = Bricks->fill('\x20');

	for (int i = 1; i < _Bricks->h; i++)
		for (int j = 2; j < _Bricks->w; j++)
			Bricks->set(j, i, '#');
}


void GameManager::CopyBricks(core::Matrix<char>* buff)
{
	for (int i = 1; i < _Bricks->h; i++)
		for (int j = 2; j < _Bricks->w; j++)
			if (Bricks->get(j, i) == '#')
				buff->set(j, i, Bricks->get(j, i));
}


void GameManager::LoadEntities()
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
            else
				GameBuff->set(j, i, '\x20');
            

            for (int Itr = 0; Itr < 27; Itr++)
            {
				if ((playerX == (j + Itr)) && (playerY == i))
					GameBuff->set(j, playerY, '\xDB');
            }
		}
	}
}


void GameManager::_Init_Print()
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


void GameManager::PrintGameBoard(core::Matrix<char>* buff)
{
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


void GameManager::PrintGame()
{

	CopyBricks(GameBuff);
	PrintGameBoard(GameBuff);
	ClearBuffer(GameBuff, _Gameboard);

	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", score, highscore);
}


void GameManager::GameWindow()
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

void GameManager::_Init_()
{
	Screen->fill('\x20');
	Border->fill('\x20');
	GameBuff->fill('\x20');
	EntryBuff->fill('\x20');
	Bricks->fill('\x20');


	CreateBorder();
	CreateBricks();
}


void GameManager::MainMenu(colour_t val)
{
	// code that prints title from a *.txt file

	xcon::console_print(( (_Screen->w / 2) - 6 ), ( _Screen->h - 10), val, "Start (Space)");
	xcon::console_print(( (_Screen->w / 2) - 8 ), ( _Screen->h - 9), val, "Controls Menu (C)");
	xcon::console_print(( (_Screen->w / 2) - 7 ), ( _Screen->h - 8), val, "Leaderboard (V)");
	xcon::console_print(( (_Screen->w / 2) - 6 ), ( _Screen->h - 7), val, "Quit Game (X)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == '\x20')
		{
			main_menu = false;
			quit_game = false;
			xcon::clear_console();
		}

		if (current == 'c' || current == 'C')
		{
			main_menu = false;
			c_menu = true;
			xcon::clear_console();
		}

		if (current == 'v' || current == 'V')
		{
			main_menu = false;
			l_menu = true;
			xcon::clear_console();
		}

		if (current == 'x' || current == 'X')
		{
			main_menu = false;
			runtime = false;
			xcon::clear_console();
		}
	}
}

void GameManager::ControlsMenu(colour_t val)
{
	xcon::console_print(((_Screen->w / 2) - 4), (_Screen->h - 18), YELLOW, "Controls:");
	xcon::console_print(((_Screen->w / 2) - 14), (_Screen->h - 17), YELLOW, "-----------------------------");

	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 16), val, "Move Left           (A)");
	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 15), val, "Move Right          (D)");
	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 14), val, "Pause               (E)");
	xcon::console_print(((_Screen->w / 2) - 11), (_Screen->h - 13), val, "Quit Current Game   (Q)");

	xcon::console_print(((_Screen->w / 2) - 14), (_Screen->h - 10), YELLOW, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 5), (_Screen->h - 7), RED, "Return  (X)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			c_menu = false;
			main_menu = true;
			xcon::clear_console();
		}
	}
}


void GameManager::LeaderboardMenu(colour_t val)
{
	// code that loads leaderboard from disc
	xcon::console_print(((_Screen->w / 2) - 5 ), (_Screen->h / 2), CYAN, "Leaderboard");
	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) + 1), CYAN, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 5), ((_Screen->h / 2) + 2), RED, "Return  (X)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			l_menu = false;
			main_menu = true;
			xcon::clear_console();
		}
	}
}


void GameManager::PauseMenu(colour_t val)
{
	xcon::console_print(((_Screen->w / 2) - 3), ((_Screen->h / 2) - 2), YELLOW, "Paused:");
	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) - 1), YELLOW, "-----------------------------");

	//xcon::f_console_print(((_Screen->w / 2) - 4), (_Screen->h / 2), "\033[21;%dm%s\033[0m\n", aBLACK, score);
	xcon::f_console_print(((_Screen->w / 2) - 4), (_Screen->h / 2), BLUE, "Score: %d", score);

	xcon::console_print(((_Screen->w / 2) - 5), ((_Screen->h / 2) + 1), val, "Resume (E)");
	xcon::console_print(((_Screen->w / 2) - 8), ((_Screen->h / 2) + 2), val, "Controls Menu (C)");
	xcon::console_print(((_Screen->w / 2) - 7), ((_Screen->h / 2) + 3), val, "Leaderboard (V)");
	xcon::console_print(((_Screen->w / 2) - 7), ((_Screen->h / 2) + 4), GREEN, "Save Game (S)");

	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) + 5), YELLOW, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 10), ((_Screen->h / 2) + 6), RED, "Quit to Main Menu (X)");
	xcon::console_print(((_Screen->w / 2) - 10), ((_Screen->h / 2) + 7), RED, "Quit Current Game (Q)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'e' || current == 'E')
		{
			pause = false;
			quit_game = false;
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
			main_menu = false;
			l_menu = true;
			xcon::clear_console();
		}

		if (current == 'x' || current == 'X')
		{
			pause = false;
			main_menu = true;
			init = false;
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


// Main Runtime method
void GameManager::Run()
{
	xcon::clear_console();
	
	if (!init)
		_Init_();
	
	do
	{				
		while (main_menu)
		{
			MainMenu(WHITE);
			//ClearAll();
		}

		while (c_menu)
		{
			ControlsMenu(WHITE);
			//ClearAll();
		}

		while (l_menu)
		{
			LeaderboardMenu(WHITE);
			//ClearAll();
		}

		while (pause)
		{
			PauseMenu(WHITE);
			//ClearAll();
		}

		while (!quit_game)
		{
			GameWindow();
			//ClearAll();
		}

	} while (runtime);

	// Eventually, load in a Gameover screen
	xcon::clear_console();
	xcon::console_print("Game Over!", RED);

}