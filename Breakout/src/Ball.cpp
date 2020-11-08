#include "Ball.h"

Ball::Ball(int posX, int posY)
{
	srand((unsigned int)time(NULL));
	originalBallX = posX;
	originalBallY = posY;
	ballX = posX;
	ballY = posY;
	ballDir = eDir::STOP;
	resetBallDir = eDir::STOP;
}

void Ball::Reset()
{
	ballX = originalBallX;
	ballY = originalBallY;
	ballDir = eDir::STOP;	
}

void Ball::randomDir()
{
	// ballDir = (eDir)(rand() % 8 + 1);

	if (ballDir == eDir::UP)
		ballDir = eDir::DOWN;
	else if (ballDir == eDir::UPLEFT)
		ballDir = eDir::DOWNLEFT;
	else if (ballDir == eDir::UPRIGHT)
		ballDir = eDir::DOWNRIGHT;
}

void Ball::Move()
{
	switch (ballDir)
	{
	case eDir::STOP:
		break;

	case eDir::LEFT:
		ballX--;
		break;

	case eDir::RIGHT:
		ballX++;
		return;

	case eDir::UPLEFT:
		ballX--; ballY--;
		break;

	case eDir::DOWNLEFT:
		ballX--; ballY++;
		break;

	case eDir::UPRIGHT:
		ballX++; ballY--;
		break;

	case eDir::DOWNRIGHT:
		ballX++; ballY++;
		break;

	case eDir::UP:
		ballY--;
		break;

	case eDir::DOWN:
		ballY++;
		break;

	default:
		break;
	}
}