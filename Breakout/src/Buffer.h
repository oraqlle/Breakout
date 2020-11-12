#include <string>
#include "ConsoleSettings.h"
#include "Ball.h"
#include "Paddle.h"
#include "posxy.h"
#include "rectangle.h"

class Buffer
{
private:	
	char c_border;

public:
	bool init;
	
	char mainBuffer[100][100] = { '\x00' };
	char borderBuffer[100][100] = { '\x00' };
	char prevBuffer[100][100] = { '\x00' };
	char emptyBuffer[100][100] = { '\x00' };

	rectangle* _Border;
	rectangle* _Gameboard;
	rectangle* _BrickSize;

	posxy* _null;
	posxy* _endline;


	Ball* ball;
	Paddle* player;
	ConsoleSettings* Console;

public:
	Buffer(rectangle* _border, rectangle* _gameboard,
		char borderDesign, Ball* _Ball, Paddle* _Player,
		ConsoleSettings* _Console);
	~Buffer();

	void EmptyFullBuffer();

	void CreateEmptyBuffer();
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
	inline char ScanBuffer(int& _col, int& _row) const
	{ return prevBuffer[_col][_row]; }

	void SetBuffer(int& _col, int& _row, const char& _val);
};