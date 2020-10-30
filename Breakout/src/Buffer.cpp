#include "Buffer.h"

Buffer::Buffer(int& _w, int& _h, char borderDesign, Ball* _Ball, Paddle* _Player,
	ConsoleSettings* _Console)
	: _width(_w), _height(_h), c_border(borderDesign)
{
	inner_w = _w - 3;
	inner_h = _h - 2;

	ball = new Ball(inner_w / 2, inner_h - 4);
	player = new Paddle(inner_w / 2, inner_h - 3);
	Console = _Console;
}

Buffer::~Buffer()
{
	delete Console;
}

// Emptying Buffers
void Buffer::EmptyFullBuffer()
{
	for (int row = 0; row < _height; row++)
	{
		for (int column = 0; column < _width - 1; column++)
		{
			borderBuffer[column][row] = { '\x20' };
		}
	}
}

void Buffer::ClearGameBuffer()
{
	for (int row = 0; row < inner_h; row++)
	{
		for (int column = 0; column < inner_w; column++)
		{
			mainBuffer[column][row] = { '\x20' };
		}
	}
}

// Creates the border buffer
void Buffer::CreateBorder()
{
	for (int column = 0; column < _width - 1; column++)
	{
		borderBuffer[column][0] = { c_border };
	}

	for (int row = 0; row < _height; row++)
	{
		for (int column = 0; column < _width - 1; column++)
		{
			if (column == 0)
			{
				borderBuffer[column][row] = { c_border };
			}

			if (column == _width - 2)
			{
				borderBuffer[column][row] = { c_border };
				int offset = column + 1;
				borderBuffer[offset][row] = { '\n' };
			}
		}
	}

	for (int column = 0; column < _width - 1; column++)
	{
		borderBuffer[column][(_height - 1)] = { c_border };
	}
}

// Creates the main game buffer
void Buffer::GameBuffer()
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	for (int i = 0; i < inner_h; i++)
	{
		for (int j = 0; j < inner_w; j++)
		{
			if (ballX == j && ballY == i)
			{
				mainBuffer[ballX][ballY] = { '@' };
			}

			else if (playerX - 4 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX - 3 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX - 2 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX - 1 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX == j && playerY == i)
			{
				mainBuffer[playerX][playerY] = { '\xDB' };
			}
			else if (playerX + 1 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 2 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 3 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 4 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}

			else
			{
				mainBuffer[j][i] = { '\x20' };
			}
		}
	}
}

// Printing Buffers
void Buffer::PrintBorder()
{
	CreateBorder();
	for (int row = 0; row < _height; row++)
	{
		for (int column = 0; column < _width; column++)
		{
			char z = borderBuffer[column][row];
			printf("%c", z);
		}
	}
}

void Buffer::PrintGameBuffer()
{
	GameBuffer();
	for (int row = 0; row < inner_h; row++)
	{
		Console->setCurser(1, (row + 1), false);
		for (int column = 0; column < inner_w; column++)
		{
			printf("%c", mainBuffer[column][row]);
		}
	}
	ClearGameBuffer();
}