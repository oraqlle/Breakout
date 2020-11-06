#pragma once
#include <iostream>
#include <Windows.h>

class ConsoleSettings
{
private:
public:
	ConsoleSettings(int x = 0, int y = 0);

	void setCurser(int x, int y, bool visibility);

	void setTextColour(const char* colour);
	void consolePrint(const char* colour, const char* text);

	void ClearConsole();
};

