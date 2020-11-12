#pragma once
#include <Windows.h>
#include <time.h>
#include "Direction.h"
#include "posxy.h"
#include "rectangle.h"

class Ball
{
private:
	int originalPosX;
	int originalPosY;

	eDir ballDir;
	eDir resetBallDir;

	posxy* ballPos;

public:
	Ball(posxy* _BallStart);
	void Reset();

	void randomDir();
	inline void chanegDir(eDir d) { ballDir = d; }

	inline int getX() { return ballPos->x; }
	inline int getY() { return ballPos->y; }
	inline posxy getPos() { return (*ballPos); }
	inline eDir getDirection() { return ballDir; }

	void Move();
};