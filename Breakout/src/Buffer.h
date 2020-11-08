#include <string>
#include "ConsoleSettings.h"
#include "Ball.h"
#include "Paddle.h"

class Buffer
{
private:
	int _width;
	int _height;
	int inner_w;
	int inner_h;
	
	char c_border;

public:
	bool init;

	char mainBuffer[100][100];
	char borderBuffer[100][100];
	char prevBuffer[100][100];

private:
	Ball* ball;
	Paddle* player;
	ConsoleSettings* Console;

public:
	Buffer(int& _w, int& _h, char borderDesign, Ball* _Ball,
		Paddle* _Player, ConsoleSettings* _Console);
	~Buffer();

	void EmptyFullBuffer();
	void CreateBorder();
	void PrintBorder();
	void PrintGameBuffer();
	void CreateBricks();

	void GameBuffer();
	void ClearGameBuffer();

	inline char ScanBuffer(int& _col, int& _row) const
	{ return prevBuffer[_col][_row]; }

	void SetBuffer(int& _col, int& _row, const char& _val);
};