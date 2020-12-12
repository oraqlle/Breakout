#pragma once

#include <string>
#include "ConsoleSettings.h"
#include "Ball.h"
#include "Paddle.h"
#include "posxy.h"
#include "rectangle.h"
#include "defines.h"

template<class _Ty>
class BufferStream
{
private:
	_Ty c_border;

public:
	bool init;

	int max_height;
	int max_width;
	
	/*char mainBuffer[BUFFERMAX][BUFFERMAX] = { '\x00' };
	char borderBuffer[BUFFERMAX][BUFFERMAX] = { '\x00' };
	char prevBuffer[BUFFERMAX][BUFFERMAX] = { '\x00' };*/

	_Ty null_buffer[BUFFERMAX][BUFFERMAX] = { 0 };
	_Ty buffer[BUFFERMAX][BUFFERMAX] = { '\x00' };

	rectangle* dimensions;
	posxy* _null;
	posxy* _endline;
	Ball* ball;
	Paddle* player;
	ConsoleSettings* Console;

public:
	
	BufferStream(
		_Ty borderDesign,
		Ball* _Ball,
		Paddle* _Player,
		ConsoleSettings* _Console,
		rectangle* _Dimensions
	);

	~BufferStream();

	void buffer_printf(
		_Ty mtrx[][BUFFERMAX]
	);

	void print_null_buffer();

	void empty_buffer(
		_Ty mtrx[][BUFFERMAX]
	);

	void CreateBorder();
	void PrintBorder();
	
	void PrintEmptyBuffer();
	void GameBuffer();
	void PrintGameBuffer();
	void ClearGameBuffer();

private:
	void CreateBricks();
	void LoadBricks();

public:
	inline char buffer_scanf(
		int& _col, 
		int& _row
	) const
	{ return prevBuffer[_col][_row]; }

	void set_buffer(
		int& _col, 
		int& _row, 
		const char& _val
	);
};