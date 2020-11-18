#pragma once
#include <Windows.h>
#include "posxy.h"

class Paddle
{
private:
	posxy* paddlePos;
	int originalPosX;
	int originalPosY;

public:
	Paddle(posxy* _paddleStart);

	void Reset();

	inline int getX() { return paddlePos->x; }
	inline int getY() { return paddlePos->y; }
	inline posxy getPos() { return (*paddlePos); }

	inline void moveLeft() { paddlePos->x -= 2; }
	inline void moveRight() { paddlePos->x += 2; }
};

