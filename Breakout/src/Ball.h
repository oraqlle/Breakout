#pragma once
#include <Windows.h>
#include "Direction.h"

class Ball
{
private:
	int ballX, ballY;
	int originalBallX, originalBallY;
	eDir ballDir;
	eDir prevBallDir;

public:
	Ball(int posX, int posY);

	void Reset();

	void chanegDir(eDir d);

	inline int getX() { return ballX; }
	inline int getY() { return ballY; }
	inline eDir getDirection() { return ballDir; }

	void Move();
};