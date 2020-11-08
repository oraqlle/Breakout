#include "GameManager.h"

GameManager::GameManager(int w, int h)
{
	srand((unsigned int)time(NULL));

	quit = false;
	start = false;
	endgame = false;

	left = 'a'; right = 'd';

	score = 00;
	highscore = 00;

	width = w; height = h;
	inner_w = w - 3;
	inner_h = h - 2;

	startX = ((inner_w / 2) - 13);
	startY = inner_h - 3;
	ballStartX = inner_w / 2;
	ballStartY = inner_h - 6;

	ball = new Ball(ballStartX, ballStartY);
	player = new Paddle(startX, startY);

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
	Console->setCurser((width + 5), (height - 24), false);
	printf("Score: %d | High Score: %d", score, highscore);

	HighScore(score);
}

// Highscore Tracker
void GameManager::HighScore(int& _score)
{
	_score > highscore ? highscore = _score : NULL;
}

// Restarts the Game
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
		if (current == 's' || current == 'S')
			start = true;
	}
}

// Checks Buffer if their are Bricks at the Ball's location
void GameManager::BrickCollision(int& _ballX, int& _ballY)
{
	for (int i = 0; i < inner_h; i++)
	{
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
					ball->chanegDir(eDir::UPRIGHT);
					break;

				case eDir::DOWNRIGHT:
					ball->chanegDir(eDir::DOWNLEFT);
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

		if (current == left)
			if (PlayerX > 0)
				player->moveLeft();

		if (current == right)
			if (PlayerX < inner_w)
				player->moveRight();

		if (ball->getDirection() == eDir::STOP)
		{
			ball->chanegDir(eDir::DOWN);
			ball->Move();
		}

		if (current == 'q')
		{
			quit = true;
			endgame = true;
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
		mainBuffer->PrintBorder();
		Console->setCurser((width + 5), (height - 24), false);
		printf("Score: %d | High Score: %d", score, highscore);

		while (!start)
		{
			Console->setCurser(((width / 2) - 9), (height - 16), false);
			Console->consolePrint("Cyan", "Press S to start");
			Start();
			Console->setTextColour("White");
		}

		while (!quit)
		{
			mainBuffer->PrintGameBuffer();
			Input();
			Logic();

			Console->setCurser((width + 5), (height - 24), false);
			printf("Score: %d | High Score: %d", score, highscore);
		}

		GameOver();
	
		Console->setCurser(0, (height + 1), false);
		Console->setTextColour("White");

	}
}