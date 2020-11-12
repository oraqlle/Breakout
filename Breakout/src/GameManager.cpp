#include "GameManager.h"

GameManager::GameManager(int w, int h)
{
	// rand() seed
	srand((unsigned int)time(NULL));

	// Text offset
	const int oset = w + 5;

	// Control booleans
	quit = false;
	start = false;
	restartKey = false;
	endgame = false;
	pause = false;
	
	// scores
	score = 00;
	highscore = 00;

	// Game Sizes
	_Border = new rectangle{ w, h };
	_Gameboard = new rectangle{ (w - 3), (h - 2) };

	// Ball and Player Positions
	_StartPos = new posxy{ ((_Gameboard->w / 2) - 13), (_Gameboard->h - 3) };
	_BallStart = new posxy{ (_Gameboard->w / 2), (_Gameboard->h - 6) };
	
	// Endpoints
	_null = new posxy{ 0, 0 };
	_endline = new posxy{ 0, (_Border->h + 1) };

	// Text Positions
	_ScorePos = new posxy{ oset, (h- 24) };
	_StartText = new posxy{ oset, (h - 23) };

	_GameOver = new posxy{ oset, (h - 23) };
	_PlayAgain = new posxy{ oset, (h - 22) };
	_YesNo = new posxy{ oset, (h - 21) };

	_ControlText = new posxy{ oset, (h - 19) };
	_Line2 = new posxy{ oset, (h - 18) };
	_aLeft = new posxy{ oset, (h - 17) };
	_dRight = new posxy{ oset, (h - 16) };
	_ePause = new posxy{ oset, (h - 15) };
	_qQuit = new posxy{ oset, (h - 14) };

	_PauseText = new posxy{ oset, (h - 12) };
	_Line1 = new posxy{ oset, (h - 11) };
	_Continue = new posxy{ oset, (h - 10) };
	_Restart = new posxy{ oset, (h - 9) };
	_Quit = new posxy{ oset, (h - 8) };

	// External Objects
	ball = new Ball(_BallStart);
	player = new Paddle(_StartPos);
	Console = new ConsoleSettings();
	mainBuffer = new Buffer(_Border, _Gameboard, '\xB2', ball, player, Console);
}

// Destructor
GameManager::~GameManager()
{
	delete _Border, _Gameboard, _StartPos, _BallStart, _null, _endline;
	delete _ScorePos, _StartText, _GameOver, _PlayAgain, _YesNo;
	delete _ControlText, _Line2, _aLeft, _dRight, _ePause, _qQuit;
	delete _PauseText, _Line1, _Continue, _Restart, _Quit;
	delete ball, player, Console, mainBuffer;
}

// Score Tracker
void GameManager::ScoreUp()
{
	score += 10;
	Console->setCurser(_ScorePos, false);
	Console->textColour("Blue");
	printf("Score: %d | High Score: %d", score, highscore);

	HighScore(score);
}

// Highscore Tracker
void GameManager::HighScore(int& _score)
{
	_score > highscore ? highscore = _score : NULL;
}

// Restarts the Game (in pause menu)
void GameManager::Restart()
{
	mainBuffer->EmptyFullBuffer();

	quit = false;
	start = false;
	endgame = false;
	pause = false;
	restartKey = false;

	ball->Reset();
	player->Reset();
	score = 0;

	Console->setCurser(_null, false);
	Console->ClearConsole();
	mainBuffer->init = false;
}

// Restarts the Game (if player loses)
void GameManager::Restart(const char& _key)
{
	if (_key == 'Y' || _key == 'y')
	{
		mainBuffer->EmptyFullBuffer();

		quit = false;
		start = false;
		endgame = false;
		pause = false;
		restartKey = false;

		ball->Reset();
		player->Reset();
		score = 0;

		Console->setCurser(_null, false);
		Console->ClearConsole();
		mainBuffer->init = false;
	}
	else if (_key == 'N' || _key == 'n')
	{
		endgame = true;
	}
}

// Runs when the player loses or quits
void GameManager::GameOver()
{
	mainBuffer->PrintGameBuffer();

	Console->Log(_GameOver, "Red", "Game Over!", false);

	Console->Log(_PlayAgain, "Green", "Play Again", false);

	Console->Log(_YesNo, "White", "[Y/N]: ", false);

	char playAgain;
	#pragma warning(suppress : 4996)
	scanf("%c", &playAgain);

	Restart(playAgain);
}

// Very Simple Start Screen
void GameManager::Start()
{
	if (_kbhit())
	{
		char current = _getch();
		current == 's' || current == 'S' ? start = true : NULL;
	}
}

// Dispays the Controls
void GameManager::ControlMenu()
{
	Console->Log(_ControlText, "Yellow", "Controls:", false);

	Console->Log(_Line2, "Yellow", "------------", false);

	Console->Log(_aLeft, "Cyan", "a - Moves Paddle Left", false);

	Console->Log(_dRight, "Cyan", "d - Moves Paddle Right", false);

	Console->Log(_ePause, "Cyan", "e - Pause Game", false);

	Console->Log(_qQuit, "Cyan", "q - Quit Game", false);

	Console->setCurser(_endline, false);
}

void GameManager::ClearPause()
{
	Console->Log(_PauseText, "Black", "Game Paused:", false);

	Console->Log(_Line1, "Black", "------------", false);

	Console->Log(_Continue, "Black", ">> Continue (E)", false);

	Console->Log(_Restart, "Black", ">> Restart (R)", false);

	Console->Log(_Quit, "Black", ">> Quit (Q)", false);

	Console->setCurser(_endline, false);
}

void GameManager::Pause()
{
	while (pause)
	{

		Console->Log(_PauseText, "Yellow", "Game Paused:", false);

		Console->Log(_Line1, "Yellow", "------------", false);

		Console->Log(_Continue, "Cyan", ">> Continue (E)", false);

		Console->Log(_Restart, "Cyan", ">> Restart (R)", false);

		Console->Log(_Quit, "Cyan", ">> Quit (Q)", false);

		Console->setCurser(_endline, false);
	
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
		}
	}
}

// Checks Buffer if their are Bricks at the Ball's location
void GameManager::BrickCollision(int& _ballX, int& _ballY)
{
	for (int i = 0; i < _Gameboard->h; i++)
		for (int j = 0; j < _Gameboard->w; j++)
		{
			char _val = mainBuffer->ScanBuffer(j, i);
			if ((_val == '#') && (_ballX == j && _ballY == i))
			{
				mainBuffer->SetBuffer(j, i, '\x20');
				ScoreUp();
				ball->randomDir();
			}
		}
}

// Checks if the ball has collided with the paddle
void GameManager::PaddleCollision(int& _ballX, int& _ballY, 
	int& _playerX, int& _playerY)
{
	for (int i = 0; i < 26; i++)
		if (_ballY == _playerY - 1)
			if (_ballX == _playerX + i)
			{
				eDir dir = ball->getDirection();
				switch (dir)
				{
				case eDir::DOWNLEFT:
					ball->chanegDir(eDir::UPLEFT);
					break;

				case eDir::DOWNRIGHT:
					ball->chanegDir(eDir::UPRIGHT);
					break;

				case eDir::DOWN:
					ball->chanegDir((eDir)((rand() % 3) + 1));
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

		if (ball->getDirection() == eDir::STOP)
		{
			ball->chanegDir(eDir::DOWN);
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
		ball->chanegDir(ball->getDirection() == eDir::UPRIGHT ? eDir::DOWNRIGHT : eDir::DOWNLEFT);

	// Right wall collision
	if (ballX == _Gameboard->w - 1)
		ball->chanegDir(ball->getDirection() == eDir::UPRIGHT ? eDir::UPLEFT : eDir::DOWNLEFT);

	// Left wall collision
	if (ballX == (_Gameboard->w + 1) - _Gameboard->w)
		ball->chanegDir(ball->getDirection() == eDir::UPLEFT ? eDir::UPRIGHT : eDir::DOWNRIGHT);
}

// Main Runtime method
void GameManager::Run()
{
	while (!endgame)
	{
		Console->setCurser(_null, false);
		mainBuffer->EmptyFullBuffer();
		mainBuffer->CreateEmptyBuffer();
		mainBuffer->PrintBorder();
		mainBuffer->PrintGameBuffer();

		ControlMenu();
		Console->setCurser(_ScorePos, false);
		Console->textColour("Blue");
		printf("Score: %d | High Score: %d", score, highscore);

		while (!start)
		{
			Console->Log(_StartText, "Pink", "Start (S)", false);
			Start();
		}

		while (!quit)
		{
			Console->Log(_StartText, "Black", "Start (S)", false);
			Console->Log(_endline, "White", "\x20", false);
			mainBuffer->PrintGameBuffer();
			Input();
			Logic();

			ControlMenu();
			Console->setCurser(_ScorePos, false);
			Console->textColour("Blue");
			printf("Score: %d | High Score: %d", score, highscore);
		}

		if (restartKey)
			Restart();
		else 
			GameOver();
	
		Console->setCurser(_endline, false);
		Console->textColour("White");
	}
}

void GameManager::PrintTest()
{
	Console->setCurser(_null, false);
	mainBuffer->EmptyFullBuffer();
	mainBuffer->CreateEmptyBuffer();
	mainBuffer->PrintBorder();
	Console->setCurser(_endline, false);
	
	Console->Log(_PauseText, "Yellow", "Game Paused:", false);
	Console->Log((_PauseText + 1), "Yellow", "------------", false);
}