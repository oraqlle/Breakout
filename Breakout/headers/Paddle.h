#pragma once
#include <Windows.h>
#include "containers.h"

class Paddle
{
private:
	core::posxy* paddlePos;
	int originalPosX;
	int originalPosY;

public:
	Paddle(core::posxy* _paddleStart);

	void Reset();

	inline int getX() { return paddlePos->x; }
	inline int getY() { return paddlePos->y; }
	inline core::posxy getPos() { return (*paddlePos); }

	inline void moveLeft() { paddlePos->x -= 2; }
	inline void moveRight() { paddlePos->x += 2; }
};

