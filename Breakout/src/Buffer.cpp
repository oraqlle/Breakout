#include "Buffer.h"

Buffer::Buffer(int& _w, int& _h, char borderDesign, Ball* _Ball, 
	Paddle* _Player, ConsoleSettings* _Console)
	: _width(_w), _height(_h), c_border(borderDesign)
{
	inner_w = _w - 3;
	inner_h = _h - 2;

	ball = _Ball;
	player = _Player;
	Console = _Console;
}

Buffer::~Buffer()
{
	delete ball, player, Console;
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
		borderBuffer[column][(inner_h + 1)] = { c_border };
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
				mainBuffer[ballX][ballY] = { 'O' };
			}

			else if (playerX == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
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
			else if (playerX + 5 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 6 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 7 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 8 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 9 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 10 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 11 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 12 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 13 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 14 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 15 == j && playerY == i)
			{
				mainBuffer[j][playerY] = { '\xDB' };
			}
			else if (playerX + 16 == j && playerY == i)
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

void Buffer::CreateBricks()
{
	for (int i = ((_height + 1) - _height); i < (_height - 19); i++)
	{
		for (int j = ((_width + 2) - _width); j < (_width - 5); j++)
		{
			mainBuffer[j][i] = { '#' };
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
	CreateBricks();
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