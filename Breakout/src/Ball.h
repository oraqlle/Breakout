#pragma once
#include <Windows.h>
#include <time.h>
#include "Direction.h"

class Ball
{
private:
	int ballX, ballY;
	int originalBallX, originalBallY;
	eDir ballDir;
	eDir resetBallDir;

public:
	Ball(int posX, int posY);
	void Reset();

	void randomDir();
	inline void chanegDir(eDir d) { ballDir = d; }

	inline int getX() { return ballX; }
	inline int getY() { return ballY; }
	inline eDir getDirection() { return ballDir; }

	void Move();
};