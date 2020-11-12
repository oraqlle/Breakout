#include "Ball.h"

Ball::Ball(posxy* _ballStart)
{
	srand((unsigned int)time(NULL));

	originalPosX = _ballStart->x;
	originalPosY = _ballStart->y;
	ballPos = _ballStart;

	ballDir = eDir::STOP;
	resetBallDir = eDir::STOP;
}

void Ball::Reset()
{
	ballPos->x = originalPosX;
	ballPos->y = originalPosY;
	ballDir = eDir::STOP;	
}

void Ball::randomDir()
{
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
		ballPos->x--;
		break;

	case eDir::RIGHT:
		ballPos->x++;
		return;

	case eDir::UPLEFT:
		ballPos->x--, ballPos->y--;
		break;

	case eDir::DOWNLEFT:
		ballPos->x--; ballPos->y++;
		break;

	case eDir::UPRIGHT:
		ballPos->x++; ballPos->y--;
		break;

	case eDir::DOWNRIGHT:
		ballPos->x++; ballPos->y++;
		break;

	case eDir::UP:
		ballPos->y--;
		break;

	case eDir::DOWN:
		ballPos->y++;
		break;

	default:
		break;
	}
}