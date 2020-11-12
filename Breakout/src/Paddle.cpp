#include "Paddle.h"

Paddle::Paddle(posxy* _paddleStart)
{
	paddlePos = _paddleStart;
	originalPos = { _paddleStart->x, _paddleStart->y };
}