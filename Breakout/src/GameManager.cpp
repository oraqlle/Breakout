#include "GameManager.h"

GameManager::GameManager(int w, int h)
{
	srand(time(NULL));

	quit = false;
	start = false;
	endgame = false;

	left = 'a'; right = 'd';

	score = 0;

	width = w; height = h;
	inner_w = w - 3;
	inner_h = h - 2;

	startX = ((inner_w / 2) - 8);
	startY = inner_h - 3;
	ballStartX = inner_w / 2;
	ballStartY = inner_h - 6;

	ball = new Ball(ballStartX, ballStartY);
	player = new Paddle(startX, startY);

	Console = new ConsoleSettings();
	mainBuffer = new Buffer(w, h, '\xB2', ball, player, Console);
}

GameManager::~GameManager()
{
	delete ball, player, Console, mainBuffer;
}

// Score Tracker
void GameManager::ScoreUp()
{
	score += 10;

	Console->setCurser(0, (height + 2), false);
	printf("Score: %d\n", score);
	Console->setCurser(0, (height + 3), false);

	ball->Reset();
	player->Reset();
}

void GameManager::Restart(const char& _key)
{
	if (_key == 'Y' || _key == 'y')
	{
		mainBuffer->EmptyFullBuffer();
		quit = false;
		start = false;
		ball->Reset();

		Console->setCurser(0, 0, false);
		Console->ClearConsole();
	}
	else if (_key == 'N' || _key == 'n')
	{
		endgame = true;
	}
}

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
			quit = true;
	}
}

void GameManager::Start()
{
	if (_kbhit())
	{
		char current = _getch();
		if (current == 's')
			start = true;
	}
}

void GameManager::Logic()
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	for (int i = 0; i < 15; i++)
		if (ballY == playerY - 1)
			if (ballX == playerX + i)
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

void GameManager::GameOver()
{
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

void GameManager::Run()
{
	while (!endgame)
	{
		Console->setCurser(0, 0, false);
		mainBuffer->EmptyFullBuffer();
		mainBuffer->PrintBorder();

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
			printf("Score: %d\n", score);
			//Console->setCurser((width + 5), (height - 26), false);
		}

		GameOver();
	
		Console->setCurser(0, (height + 1), false);
		Console->setTextColour("White");

	}
}