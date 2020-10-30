#include "Ball.h"

Ball::Ball(int posX, int posY)
{
	originalBallX = posX;
	originalBallY = posY;
	ballX = posX;
	ballY = posY;
	ballDir = eDir::STOP;
	prevBallDir = ballDir;
}

void Ball::Reset()
{
	ballX = originalBallX;
	ballY = originalBallY;
	ballDir = eDir::STOP;
	prevBallDir = ballDir;
}

void Ball::chanegDir(eDir d)
{
	ballDir = d;
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