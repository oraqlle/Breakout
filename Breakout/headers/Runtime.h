#pragma once
#include "..\headers\GameEngine.h"
#include <vector>


class Runtime
{
private:
	int w, h;
	GameEngine* engine;


public:
	Runtime(int _w, int _h);
	~Runtime();

	int Run();
};

