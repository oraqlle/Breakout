#include "Paddle.h"
Paddle::Paddle()
{
	paddleX = paddleY = 0;
	originalPaddleX = originalPaddleY = 0;
}

Paddle::Paddle(int posX, int posY)
{
	originalPaddleX = posX;
	originalPaddleY = posY;
	paddleX = posX;
	paddleY = posY;
}