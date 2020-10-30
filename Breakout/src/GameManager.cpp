#include "GameManager.h"

GameManager::GameManager(int w, int h)
{
	srand(time(NULL));

	quit = false;

	left = 'a'; right = 'd';

	score = 0;

	width = w; height = h;
	inner_w = w - 3;
	inner_h = h - 2;

	ball = new Ball(inner_w / 2, inner_h - 4);
	player = new Paddle(inner_w / 2, inner_h - 3);

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

void GameManager::Input()
{
	ball->Move();

	int BallX = ball->getX();
	int BallY = ball->getY();

	int PlayerX = player->getX();
	int PlayerY = player->getY();

	if (_kbhit)
	{
		char current = _getch();

		if (current == left)
			if (PlayerX > 0)
				player->moveLeft();

		if (current == right)
			if (PlayerX < inner_w + 1)
				player->moveRight();

		if (ball->getDirection() == eDir::STOP)
		{
			ball->chanegDir(eDir::UP);
			ball->Move();
		}

		if (current == 'q')
			quit = true;
	}
}

void GameManager::Logic()
{

}

void GameManager::Run()
{
	mainBuffer->EmptyFullBuffer();
	mainBuffer->PrintBorder();
	while (!quit)
	{
		mainBuffer->PrintGameBuffer();
		Input();
		Logic();

		Console->setCurser(0, (height + 2), false);
		printf("Score: %d\n", score);
		Console->setCurser(0, (height + 3), false);
	}

	Console->setCurser(0, (height + 4), false);
}