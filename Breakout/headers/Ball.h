#pragma once
#include <Windows.h>
#include <time.h>
#include "direction.h"
#include "containers.h"

class Ball
{
private:
	int originalPosX;
	int originalPosY;

	core::eDir ballDir;
	core::eDir resetBallDir;

	core::posxy* ballPos;

public:
	Ball(core::posxy* _ballStart);
	void Reset();

	void randomDir();
	inline void chanegDir(core::eDir d) { ballDir = d; }

	inline int getX() { return ballPos->x; }
	inline int getY() { return ballPos->y; }
	inline core::posxy getPos() { return (*ballPos); }
	inline core::eDir getDirection() { return ballDir; }

	void Move();
};