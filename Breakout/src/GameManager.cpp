#include "GameManager.h"

GameManager::GameManager(int w, int h)
{
	// rand() seed
	srand((unsigned int)time(NULL));

	// Control booleans
	quit = false;
	start = false;
	endgame = false;
	pause = false;
	controlMenu = false;
	
	// scores
	score = 00;
	highscore = 00;

	// Game Sizes
	_Border = new rectangle{ w, h };
	_Gameboard = new rectangle{ (w - 3), (h - 2) };

	// Ball and Player Positions
	_StartPos = new posxy{ ((_Gameboard->w / 2) - 13), (_Gameboard->h - 3) };
	_BallStart = new posxy{ (_Gameboard->w / 2), (_Gameboard->h - 6) };
	
	// Text Positions
	_ScorePos = new posxy{ (_Border->w + 5), (_Border->h- 24) };

	// External Objects
	ball = new Ball(_BallStart);
	player = new Paddle(_StartPos);
	Console = new ConsoleSettings();
	mainBuffer = new Buffer(w, h, '\xB2', ball, player, Console);
}

// Destructor
GameManager::~GameManager()
{
	delete ball, player, Console, mainBuffer;
}

// Score Tracker
void GameManager::ScoreUp()
{
	score += 10;
	Console->setCurser(_ScorePos, false);
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
	ball->Reset();
	player->Reset();
	score = 0;

	Console->setCurser(0, 0, false);
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
		ball->Reset();
		player->Reset();
		score = 0;

		Console->setCurser(0, 0, false);
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
	Console->setCurser((width + 5), (height - 23), false);
	Console->consolePrint("Red", "Game Over");

	Console->setCurser((width + 5), (height - 22), false);
	Console->consolePrint("Cyan", "Play Again?");

	Console->setCurser((width + 5), (height - 21), false);
	Console->consolePrint("White", "[Y/N]: ");

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

void GameManager::Pause()
{
	while (!pause)
	{

		Console->Log((width + 5), (height - 18), "Yellow",
			"Game Paused:", false);

		Console->Log((width + 5), (height - 17), "Yellow",
			"------------", false);

		Console->Log((width + 5), (height - 16), "Cyan",
			">> Continue (Esc)", false);

		Console->Log((width + 5), (height - 15), "Cyan",
			">> Controls (C)", false);

		Console->Log((width + 5), (height - 14), "Cyan",
			">> Restart (R)", false);

		Console->Log((width + 5), (height - 13), "Cyan",
			">> Quit (Q)", false);

		Console->setCurser(0, (height + 1), false);

		if (_kbhit())
		{
			char current = _getch();
			current == '\x1B' ? pause = true : NULL;
			current == 'c' || current == 'C' ? controlMenu = true : NULL;
			current == 'r' || current == 'R' ? pause = true : NULL;
			current == 'q' || current == 'Q' ? quit = true : NULL;
		}
	}
}

// Checks Buffer if their are Bricks at the Ball's location
void GameManager::BrickCollision(int& _ballX, int& _ballY)
{
	for (int i = 0; i < inner_h; i++)
		for (int j = 0; j < inner_w; j++)
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
			if (PlayerX < inner_w)
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

		if (current == '\x1B')
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
	if (ballY == inner_h)
		quit = true;

	// Top wall collision
	if (ballY == inner_h - inner_h)
		ball->chanegDir(ball->getDirection() == eDir::UPRIGHT ? eDir::DOWNRIGHT : eDir::DOWNLEFT);

	// Right wall collision
	if (ballX == inner_w - 1)
		ball->chanegDir(ball->getDirection() == eDir::UPRIGHT ? eDir::UPLEFT : eDir::DOWNLEFT);

	// Left wall collision
	if (ballX == (inner_w + 1) - inner_w)
		ball->chanegDir(ball->getDirection() == eDir::UPLEFT ? eDir::UPRIGHT : eDir::DOWNRIGHT);
}

// Main Runtime method
void GameManager::Run()
{
	while (!endgame)
	{
		Console->setCurser(0, 0, false);
		mainBuffer->EmptyFullBuffer();
		mainBuffer->CreateEmptyBuffer();
		mainBuffer->PrintBorder();
		Console->setCurser((width + 5), (height - 25), false);
		printf("Score: %d | High Score: %d", score, highscore);

		while (!start)
		{
			Console->Log((width + 5), (height - 23), "Cyan", 
				"Start (S)", false);
			Start();
			Console->setTextColour("White");
		}

		while (!quit)
		{
			Console->Log((width + 5), (height - 19), "White",
				"         ", false);
			mainBuffer->PrintGameBuffer();
			Input();
			Logic();

			Console->setCurser((width + 5), (height - 25), false);
			printf("Score: %d | High Score: %d", score, highscore);
		}

		GameOver();
	
		Console->setCurser(0, (height + 1), false);
		Console->setTextColour("White");
	}
}

void GameManager::PrintTest()
{
	Console->setCurser(0, 0, false);
	mainBuffer->EmptyFullBuffer();
	mainBuffer->CreateEmptyBuffer();
	mainBuffer->PrintBorder();
	/*Console->setCurser((width + 5), (height - 24), false);
	printf("Score: %d | High Score: %d", score, highscore);*/

	posxy _ScorePos = { (width + 5), (height - 24) };
	Console->setCurser(&_ScorePos, false);
	printf("Score: %d | High Score: %d", score, highscore);
}