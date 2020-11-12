#pragma once
#include <iostream>
#include <Windows.h>
#include "posxy.h"

class ConsoleSettings
{
private:
public:
	ConsoleSettings(int x = 0, int y = 0);

	void setCurser(int x, int y, bool visibility);
	void setCurser(posxy* curserPos, bool visibility);

	void setTextColour(const char* colour);

	void consolePrint(const char* colour, const char* text);

	void Log(int x, int y, const char* colour,
		const char* text, bool visibility);

	void Log(posxy* curser, const char* colour, 
		const char* text, bool visibility);

	void ClearConsole();
};

