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
	run = true;
	InStartMenu = true;
	quit = false;
	PressedStart = false;
	restartKey = false;
	endgame = false;
	pause = false;
	fromPauseMenu = false;
	
	// scores
	score = 00;
	highscore = 00;

	// Game Sizes
	_Border = new core::rectangle<size_t>{ w, h };
	_Gameboard = new core::rectangle<size_t>{ (w - 3), (h - 2) };
	_Bricks = new core::rectangle<size_t>{ (_Border->w - 5), (_Border->h - 19) };

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
	Buffer = new core::Matrix<char>(h, w);
	fstream = new FileStream(Buffer);
}

// Destructor
GameManager::~GameManager()
{
	delete _Border, _Gameboard, _StartPos, _BallStart, _null, _endline, 
		_ScorePos, _StartText1, _StartText2, _GameOver, _PlayAgain, _YesNo, 
		_ControlText, _Line2, _aLeft, _dRight, _ePause, _qQuit, 
		_PauseText, _Line1, _Continue, _Restart, _Quit, 
		ball, player, Buffer, fstream;
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

// Start Menu
void GameManager::StartMenu()
{
	xcon::console_print(*_StartText1, CYAN, "Press 'Enter' to Start");

	if (_kbhit())
	{
		char kbchar = _getch();

		if (kbchar == '\n')
		{
			InStartMenu = false;
		}
	}
}

// Restarts the Game (in pause menu)
void GameManager::Restart()
{
	Buffer->clear_matrix();

	quit = false;
	PressedStart = false;
	endgame = false;
	pause = false;
	restartKey = false;
	fromPauseMenu = false;

	ball->Reset();
	player->Reset();
	score = 0;

	xcon::set_curser(*_null);
	xcon::clear_console();
	Buffer->init = false;
}

// Restarts the Game (if player loses)
void GameManager::Restart(
	const char& _key
)
{
	if (_key == 'Y' || _key == 'y')
	{
		Buffer->clear_matrix();

		quit = false;
		PressedStart = false;
		endgame = false;
		pause = false;
		restartKey = false;
		fromPauseMenu = false;

		ball->Reset();
		player->Reset();
		score = 0;

		xcon::set_curser(*_null);
		xcon::clear_console();
		Buffer->init = false;
	}
	else if (_key == 'N' || _key == 'n')
	{
		endgame = true;
	}
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

	Restart(playAgain);
}

// Very Simple Start Screen
void GameManager::Start()
{
	if (_kbhit())
	{
		char current = _getch();
		current == 's' || current == 'S' ? PressedStart = true : NULL;
	}
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

void GameManager::Pause()
{
	while (pause)
	{

		xcon::console_print(*_PauseText, YELLOW, "Game Paused:");

		xcon::console_print(*_Line1, YELLOW, "------------");

		xcon::console_print(*_Continue, WHITE, ">> Continue (E)");

		xcon::console_print(*_Restart, WHITE, ">> Restart (R)");

		xcon::console_print(*_Quit, WHITE, ">> Quit (Q)");

		xcon::set_curser(*_endline);
	
		PauseInput();
	}
}

void GameManager::PauseInput()
{
	if (_kbhit())
	{
		char current = _getch();
		if (current == 'e' || current == 'E')
		{
			pause = false;
			ClearPause();
		}
		else if (current == 'r' || current == 'R')
		{
			pause = false;
			quit = true;
			restartKey = true;
		}
		else if (current == 'q' || current == 'Q')
		{
			pause = false;
			quit = true;
			endgame = true;
			restartKey = false;
			fromPauseMenu = true;
		}
	}
}

// Checks Buffer if their are Bricks at the Ball's location
void GameManager::BrickCollision(
	int& _ballX, 
	int& _ballY
)
{
	for (int i = 0; i < _Gameboard->h; i++)
		for (int j = 0; j < _Gameboard->w; j++)
		{
			char _val = Buffer->get(j, i);
			if ((_val == '#') && (_ballX == j && _ballY == i))
			{
				Buffer->set(j, i, '\x20');
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
			quit = true;
			endgame = true;
		}

		if (current == 'e' || current == 'E')
		{
			pause = true;
			Pause();
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
		quit = true;

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

// Main Runtime method
void GameManager::Run()
{
	while (run)
	{
		xcon::clear_console();
		xcon::set_curser(*_null);

		while (InStartMenu)
		{

		}

		while (!endgame)
		{
			xcon::set_curser(*_null);
			Buffer->clear_matrix();
			//Buffer->CreateEmptyBuffer();
			//Buffer->PrintBorder();
			//Buffer->PrintGameBuffer();

			ControlMenu();
			xcon::set_curser(*_ScorePos);
			xcon::text_colour(BLUE);
			printf("Score: %d | High Score: %d", score, highscore);

			while (!PressedStart)
			{
				xcon::console_print(*_StartText2, PINK, "Start (S)");
				Start();
			}

			while (!quit)
			{
				xcon::console_print(*_StartText2, BLACK, "Start (S)");
				xcon::console_print(*_endline, WHITE, "\x20");
				//Buffer->PrintGameBuffer();
				Input();
				Logic();

				ControlMenu();
				xcon::set_curser(*_ScorePos);
				xcon::text_colour(BLUE);
				printf("Score: %d | High Score: %d", score, highscore);
				xcon::text_colour(WHITE);
			}

			if (restartKey)
				Restart();
			else if (fromPauseMenu)
				break;
			else
				GameOver();
		}

		xcon::console_print(*_GameOver, RED, "Game Over!");
		xcon::set_curser(*_endline);
		xcon::text_colour(WHITE);
	}
}