#include "..\headers\Paddle.h"

Paddle::Paddle(posxy* _paddleStart)
{
	paddlePos = _paddleStart;
	originalPosX = _paddleStart->x;
	originalPosY = _paddleStart->y;
}

void Paddle::Reset()
{
	paddlePos->x = originalPosX;
	paddlePos->y = originalPosY;
}