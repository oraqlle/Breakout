#pragma once
#include <Windows.h>

class Paddle
{
private:
	int paddleX, paddleY;
	int originalPaddleX, originalPaddleY;

public:
	Paddle();

	Paddle(int posX, int posY);

	inline void Reset() { paddleX = originalPaddleX; paddleY = originalPaddleY; }

	inline int getX() { return paddleX; }
	inline int getY() { return paddleY; }

	inline void moveLeft() { paddleX -= 2; }
	inline void moveRight() { paddleX += 2; }
};

