#include "ConsoleSettings.h"

ConsoleSettings::ConsoleSettings(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = true; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);

	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void ConsoleSettings::setCurser(int x, int y, bool visibility)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = visibility; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);

	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void ConsoleSettings::setTextColour(const char* colour)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (colour == "Blue")
		SetConsoleTextAttribute(hOut, 9);
	else if (colour == "Green")
		SetConsoleTextAttribute(hOut, 10);
	else if (colour == "Cyan")
		SetConsoleTextAttribute(hOut, 11);
	else if (colour == "Red")
		SetConsoleTextAttribute(hOut, 12);
	else if (colour == "Pink")
		SetConsoleTextAttribute(hOut, 13);
	else if (colour == "Yellow")
		SetConsoleTextAttribute(hOut, 14);
	else if (colour == "White")
		SetConsoleTextAttribute(hOut, 15);
}

void ConsoleSettings::consolePrint(const char* colour, const char* text)
{

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (colour == "Blue")
	{
		SetConsoleTextAttribute(hOut, 9);
		std:: cout << text << std::endl;
	}
	else if (colour == "Green")
	{
		SetConsoleTextAttribute(hOut, 10);
		std:: cout << text << std::endl;
	}
	else if (colour == "Cyan")
	{
		SetConsoleTextAttribute(hOut, 11);
		std:: cout << text << std::endl;
	}
	else if (colour == "Red")
	{
		SetConsoleTextAttribute(hOut, 12);
		std:: cout << text << std::endl;
	}
	else if (colour == "Pink")
	{
		SetConsoleTextAttribute(hOut, 13);
		std:: cout << text << std::endl;
	}
	else if (colour == "Yellow")
	{
		SetConsoleTextAttribute(hOut, 14);
		std:: cout << text << std::endl;
	}
	else if (colour == "White")
	{
		SetConsoleTextAttribute(hOut, 15);
		std:: cout << text << std::endl;
	}
}
