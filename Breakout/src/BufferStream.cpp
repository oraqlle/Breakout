#include "..\headers\BufferStream.h"

#define TEMPLATE template<class _Ty>

template<class _Ty>
BufferStream<_Ty>::BufferStream(
	_Ty borderDesign, 
	Ball* _Ball, 
	Paddle* _Player, 
	ConsoleSettings* _Console, 
	rectangle* _Dimensions
)
	: c_border(borderDesign)
{
	init = false;

	// Game Sizes
	dimensions = _Dimensions;
	max_height = dimensions->h;
	max_width = dimensions->w;

	// Text Positions
	_null = new posxy{ 0, 0 };
	_endline = new posxy{ 0, (_Dimensions->h + 1) };

	ball = _Ball;
	player = _Player;
	Console = _Console;
}

// Destructor
template<class _Ty>
BufferStream<_Ty>::~BufferStream()
{
	delete dimensions, _null, _endline, ball, player, Console;
}


template<class _Ty>
void BufferStream<_Ty>::buffer_printf(
	_Ty mtrx[][BUFFERMAX]
)
{
	for (int row = 0; row < max_height; row++)
		for (int column = 0; column < max_width; column++)
		{
			_Ty z = mtrx[column][row];
			printf("%")
		}
}


// Prints the Empty Buffer
template<class _Ty>
void BufferStream<_Ty>::print_null_buffer()
{
	for (int row = 0; row < dimensions->h; row++)
		for (int column = 0; column < dimensions->w; column++)
		{
			char z = null_buffer[column][row];
			printf("%c", z);
		}
}


// Creates the Empty Buffer for Pause Screen
template<class _Ty>
void BufferStream<_Ty>::empty_buffer(
	_Ty mtrx[][BUFFERMAX]
)
{
	for (int row = 0; row < max_height; row++)
		for (int column = 0; column < max_width; column++)
			buffer[column][row] = { '\x20' };
}


// Clears only the game buffer
template<class _Ty>
void BufferStream<_Ty>::ClearGameBuffer()
{
	for (int row = 0; row < _Gameboard->h; row++)
	{
		for (int column = 0; column < _Gameboard->w; column++)
		{
			mainBuffer[column][row] = { '\x20' };
		}
	}
}


// Creates the border buffer
template<class _Ty>
void BufferStream<_Ty>::CreateBorder()
{
	for (int column = 0; column < (_Border->w - 1); column++)
	{
		borderBuffer[column][0] = { c_border };
	}

	for (int row = 0; row < _Border->h; row++)
	{
		for (int column = 0; column < _Border->w - 1; column++)
		{
			if (column == 0)
			{
				borderBuffer[column][row] = { c_border };
			}

			if (column == (_Border->w - 2))
			{
				borderBuffer[column][row] = { c_border };
				int offset = column + 1;
				borderBuffer[offset][row] = { '\n' };
			}
		}
	}

	for (int column = 0; column < (_Border->w - 1); column++)
	{
		borderBuffer[column][(_Gameboard->h + 1)] = { c_border };
	}
}


// Creates the main game buffer
template<class _Ty>
void BufferStream<_Ty>::GameBuffer()
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	for (int i = 0; i < _Gameboard->h; i++)
	{
		for (int j = 0; j < _Gameboard->w; j++)
		{
			if (ballX == j && ballY == i)
				mainBuffer[ballX][ballY] = { 'O' };

			else if (playerX == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 1 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 2 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 3 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 4 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 5 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 6 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 7 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 8 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 9 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 10 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 11 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 12 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 13 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 14 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 15 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 16 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 17 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 17 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 18 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 19 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 20 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 21 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 22 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 23 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 24 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 25 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else if (playerX + 26 == j && playerY == i)
				mainBuffer[j][playerY] = { '\xDB' };

			else
				mainBuffer[j][i] = { '\x20' };
		}
	}
}


// Creates the bricks in the main buffer
template<class _Ty>
void BufferStream<_Ty>::CreateBricks()
{
	for (int i = 1; i < _BrickSize->h; i++)
		for (int j = 2; j < _BrickSize->w; j++)
			mainBuffer[j][i] = { '#' };
}


// Loads the bricks
template<class _Ty>
void BufferStream<_Ty>::LoadBricks()
{
	for (int i = 1; i < _BrickSize->h; i++)
		for (int j = 2; j < _BrickSize->w; j++)
			if (prevBuffer[j][i] == '#')
				mainBuffer[j][i] = prevBuffer[j][i];
}


// Sets a value to the main game buffer and the bricks buffer
template<class _Ty>
void BufferStream<_Ty>::set_buffer(int& _col, int& _row, const char& _val)
{
	mainBuffer[_col][_row] = { _val };
	prevBuffer[_col][_row] = { _val };
}


// Printing Buffers
template<class _Ty>
void BufferStream<_Ty>::PrintBorder()
{
	CreateBorder();
	for (int row = 0; row < _Border->h; row++)
	{
		for (int column = 0; column < _Border->w; column++)
		{
			char z = borderBuffer[column][row];
			printf("%c", z);
		}
	}
}


// Prints only the game buffer
template<class _Ty>
void BufferStream<_Ty>::PrintGameBuffer()
{
	GameBuffer();

	if (!init)
	{
		CreateBricks();
		init = true;
	}

	LoadBricks();
	for (int row = 0; row < _Gameboard->h; row++)
	{
		Console->setCurser(1, (row + 1), false);
		for (int column = 0; column < _Gameboard->w; column++)
		{
			char z = mainBuffer[column][row];
			printf("%c", z);
			prevBuffer[column][row] = z;
		}
	}
	ClearGameBuffer();
}