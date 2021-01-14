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

	// Ball and Player Positions
	_StartPos = new core::posxy{ ((_Gameboard->w / 2) - 13), (_Gameboard->h - 3) };
	_BallStart = new core::posxy{ (_Gameboard->w / 2), (_Gameboard->h - 6) };
	
	// Endpoints and Midpoint
	_null = new core::posxy{ 0, 0 };
	_endline = new core::posxy{ 0, (_Border->h + 1) };
	_midpoint = new core::posxy{ (w / 2), (h / 2) };

	// Start Menu Text Positions
	_Title = new core::posxy{ 4, 3 };
	_StartText1 = new core::posxy{ 11, (h / 2) };

	// Text Positions
	_ScorePos = new core::posxy{ oset, (h- 24) };
	_StartText2 = new core::posxy{ oset, (h - 23) };

	_GameOver = new core::posxy{ oset, (h - 23) };
	_PlayAgain = new core::posxy{ oset, (h - 22) };
	_YesNo = new core::posxy{ oset, (h - 21) };

	_ControlText = new core::posxy{ oset, (h - 19) };
	_Line2 = new core::posxy{ oset, (h - 18) };
	_aLeft = new core::posxy{ oset, (h - 17) };
	_dRight = new core::posxy{ oset, (h - 16) };
	_ePause = new core::posxy{ oset, (h - 15) };
	_qQuit = new core::posxy{ oset, (h - 14) };

	_PauseText = new core::posxy{ oset, (h - 12) };
	_Line1 = new core::posxy{ oset, (h - 11) };
	_Continue = new core::posxy{ oset, (h - 10) };
	_Restart = new core::posxy{ oset, (h - 9) };
	_Quit = new core::posxy{ oset, (h - 8) };

	//File Names - "C:\Dev\MyGames\Breakout\Breakout\disc\title.txt"
	nTitle = "./disc/title.txt";
	nTemp = "./disc/temp.txt";
	nBaselevel = "./disc/Base_Layout.txt";
	nLevel_1 = "./disc/Level_1.txt";
	nHighScore = "./disc/HighScore.txt";

	// External Objects
	ball = new Ball(_BallStart);
	player = new Paddle(_StartPos);
	//fstream = new FileStream(Buffer);

	Screen = new core::Matrix<char>(100, 100);
	Border = new core::Matrix<char>(w, h);
	GameBuff = new core::Matrix<char>( (w - 3), (h - 2) );
	Bricks = new core::Matrix<char>( (w - 5), (h - 19) );
}

// Destructor
GameManager::~GameManager()
{
	delete _Border, _Gameboard, _StartPos, _BallStart, _null, _endline, 
		_ScorePos, _StartText1, _StartText2, _GameOver, _PlayAgain, _YesNo, 
		_ControlText, _Line2, _aLeft, _dRight, _ePause, _qQuit, 
		_PauseText, _Line1, _Continue, _Restart, _Quit, 
		ball, player, Screen, Border, Bricks/*, fstream*/;
}

// Score Tracker
void GameManager::ScoreUp()
{
	score += 10;
	xcon::set_curser(*_ScorePos);
	xcon::text_colour(BLUE);
	printf("Score: %d | High Score: %d", score, highscore);

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
void GameManager::GameOver()
{
	//Buffer->PrintGameBuffer();

	xcon::console_print(*_GameOver, RED, "Game Over!");

	xcon::console_print(*_PlayAgain, GREEN, "Play Again");

	xcon::console_print(*_YesNo, WHITE, "[Y/N]: ");

	char playAgain;
	#pragma warning(suppress : 4996)
	int temp = scanf("%c", &playAgain);

	//Restart(playAgain);
}

// Dispays the Controls
void GameManager::ControlMenu()
{
	xcon::console_print(*_ControlText, YELLOW, "Controls:");

	xcon::console_print(*_Line2, YELLOW, "------------");

	xcon::console_print(*_aLeft, CYAN, "a - Moves Paddle Left");

	xcon::console_print(*_dRight, CYAN, "d - Moves Paddle Right");

	xcon::console_print(*_ePause, CYAN, "e - Pause Game");

	xcon::console_print(*_qQuit, CYAN, "q - Quit Game");

	xcon::set_curser(*_endline);
}

void GameManager::ClearPause()
{
	xcon::console_print(*_PauseText, BLACK, "Game Paused:");

	xcon::console_print(*_Line1, BLACK, "------------");

	xcon::console_print(*_Continue, BLACK, ">> Continue (E)");

	xcon::console_print(*_Restart, BLACK, ">> Restart (R)");

	xcon::console_print(*_Quit, BLACK, ">> Quit (Q)");

	xcon::set_curser(*_endline);
}

//void GameManager::Pause()
//{
//	while (pause)
//	{
//
//		xcon::console_print(*_PauseText, YELLOW, "Game Paused:");
//
//		xcon::console_print(*_Line1, YELLOW, "------------");
//
//		xcon::console_print(*_Continue, WHITE, ">> Continue (E)");
//
//		xcon::console_print(*_Restart, WHITE, ">> Restart (R)");
//
//		xcon::console_print(*_Quit, WHITE, ">> Quit (Q)");
//
//		xcon::set_curser(*_endline);
//	
//		//PauseInput();
//	}
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
		}

		if (current == 'e' || current == 'E')
		{
			pause = true;
			//Pause();
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
		}

		if (current == 'c' || current == 'C')
		{
			main_menu = false;
			c_menu = true;
		}

		if (current == 'v' || current == 'V')
		{
			main_menu = false;
			l_menu = true;
		}

		if (current == 'x' || current == 'X')
		{
			main_menu = false;
			runtime = false;
		}
	}
}

void GameManager::ControlsMenu(colour_t val)
{
	xcon::console_print(((_Screen->w / 2) - 4), (_Screen->h - 18), val, "Controls:");
	xcon::console_print(((_Screen->w / 2) - 14), (_Screen->h - 17), val, "-----------------------------");

	xcon::console_print(((_Screen->w / 2) - 7), (_Screen->h - 16), val, "Move Left   (A)");
	xcon::console_print(((_Screen->w / 2) - 7), (_Screen->h - 15), val, "Move Right  (D)");
	xcon::console_print(((_Screen->w / 2) - 7), (_Screen->h - 14), val, "Pause       (E)");
	xcon::console_print(((_Screen->w / 2) - 7), (_Screen->h - 13), val, "Quit Game   (Q)");

	xcon::console_print(((_Screen->w / 2) - 14), (_Screen->h - 10), val, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 5), (_Screen->h - 7), val, "Return  (X)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			c_menu = false;
			main_menu = true;
		}
	}
}


void GameManager::LeaderboardMenu(colour_t val)
{
	// code that loads leaderboard from disc
	xcon::console_print(((_Screen->w / 2) - 5 ), (_Screen->h / 2), val, "Leaderboard");
	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) + 1), val, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 5), ((_Screen->h / 2) + 2), val, "Return  (X)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'x' || current == 'X')
		{
			l_menu = false;
			main_menu = true;
		}
	}
}


void GameManager::PauseMenu(colour_t val)
{
	xcon::console_print(((_Screen->w / 2) - 3), ((_Screen->h / 2) - 2), val, "Paused:");
	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) - 1), val, "-----------------------------");

	xcon::f_console_print(((_Screen->w / 2) - 4), val, (_Screen->h / 2), "Score: %d", score);

	xcon::console_print(((_Screen->w / 2) - 5), ((_Screen->h / 2) + 1), val, "Resume (E)");
	xcon::console_print(((_Screen->w / 2) - 8), ((_Screen->h / 2) + 2), val, "Controls Menu (C)");
	xcon::console_print(((_Screen->w / 2) - 7), ((_Screen->h / 2) + 3), val, "Leaderboard (V)");
	xcon::console_print(((_Screen->w / 2) - 7), ((_Screen->h / 2) + 4), val, "Save Game (S)");

	xcon::console_print(((_Screen->w / 2) - 14), ((_Screen->h / 2) + 5), val, "-----------------------------");
	xcon::console_print(((_Screen->w / 2) - 10), ((_Screen->h / 2) + 6), val, "Quit to Main Menu (X)");
	xcon::console_print(((_Screen->w / 2) - 7), ((_Screen->h / 2) + 7), val, "Quit Game (Q)");

	if (_kbhit())
	{
		char current = _getch();

		if (current == 'e' || current == 'E')
		{
			pause = false;
			quit_game = false;
		}

		if (current == 'c' || current == 'C')
		{
			pause = false;
			c_menu = true;
		}

		if (current == 'v' || current == 'V')
		{
			main_menu = false;
			l_menu = true;
		}

		if (current == 'x' || current == 'X')
		{
			pause = false;
			main_menu = true;
		}

		if (current == 'q' || current == 'Q')
		{
			pause = false;
			runtime = false;
		}
	}
}

void GameManager::GameWindow(colour_t val)
{

}


// Main Runtime method
void GameManager::Run()
{
	xcon::clear_console();

	do
	{				
		while (main_menu)
		{
			MainMenu(WHITE);
		}
		MainMenu(BLACK);

		while (c_menu)
		{
			ControlsMenu(WHITE);
		}
		ControlsMenu(BLACK);

		while (l_menu)
		{
			LeaderboardMenu(WHITE);
		}
		LeaderboardMenu(BLACK);

		while (pause)
		{
			PauseMenu(WHITE);
		}
		PauseMenu(BLACK);

		while (!quit_game)
		{
			GameWindow(WHITE);
		}
		GameWindow(BLACK);


	} while (runtime);

	// Eventually, load in a Gameover screen
	xcon::clear_console();
	xcon::console_print("Game Over!", RED);
}