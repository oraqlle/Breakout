#include "..\headers\Ball.h"

Ball::Ball(core::posxy* _ballStart)
{
	srand((unsigned int)time(NULL));

	originalPosX = _ballStart->x;
	originalPosY = _ballStart->y;
	ballPos = _ballStart;

	ballDir = core::eDir::STOP;
	resetBallDir = core::eDir::STOP;
}

void Ball::Reset()
{
	ballPos->x = originalPosX;
	ballPos->y = originalPosY;
	ballDir = core::eDir::STOP;	
}

void Ball::randomDir()
{
	if (ballDir == core::eDir::UP)
		ballDir = core::eDir::DOWN;
	else if (ballDir == core::eDir::UPLEFT)
		ballDir = core::eDir::DOWNLEFT;
	else if (ballDir == core::eDir::UPRIGHT)
		ballDir = core::eDir::DOWNRIGHT;
}

void Ball::Move()
{
	switch (ballDir)
	{
	case core::eDir::STOP:
		break;

	case core::eDir::LEFT:
		ballPos->x--;
		break;

	case core::eDir::RIGHT:
		ballPos->x++;
		return;

	case core::eDir::UPLEFT:
		ballPos->x--, ballPos->y--;
		break;

	case core::eDir::DOWNLEFT:
		ballPos->x--; ballPos->y++;
		break;

	case core::eDir::UPRIGHT:
		ballPos->x++; ballPos->y--;
		break;

	case core::eDir::DOWNRIGHT:
		ballPos->x++; ballPos->y++;
		break;

	case core::eDir::UP:
		ballPos->y--;
		break;

	case core::eDir::DOWN:
		ballPos->y++;
		break;

	default:
		break;
	}
}