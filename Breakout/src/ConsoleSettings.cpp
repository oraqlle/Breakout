#include "..\headers\ConsoleSettings.h"

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

void ConsoleSettings::setCurser(posxy* curserPos, bool visibility)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = visibility; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);

	COORD coord = { (SHORT)curserPos->x, (SHORT)curserPos->y };
	SetConsoleCursorPosition(hOut, coord);
}

void ConsoleSettings::textColour(const char* colour)
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
	else if (colour == "Black")
		SetConsoleTextAttribute(hOut, 0);
	else 
		SetConsoleTextAttribute(hOut, 15);
}

void ConsoleSettings::consolePrint(const char* colour, const char* text)
{

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (colour == "Blue")
	{
		SetConsoleTextAttribute(hOut, 9);
		printf(text);
	}
	else if (colour == "Green")
	{
		SetConsoleTextAttribute(hOut, 10);
		std::cout << text;
	}
	else if (colour == "Cyan")
	{
		SetConsoleTextAttribute(hOut, 11);
		printf(text);
	}
	else if (colour == "Red")
	{
		SetConsoleTextAttribute(hOut, 12);
		printf(text);
	}
	else if (colour == "Pink")
	{
		SetConsoleTextAttribute(hOut, 13);
		printf(text);
	}
	else if (colour == "Yellow")
	{
		SetConsoleTextAttribute(hOut, 14);
		printf(text);
	}
	else if (colour == "Black")
	{
		SetConsoleTextAttribute(hOut, 0);
		printf(text);
	}
	else if (colour == "White")
	{
		SetConsoleTextAttribute(hOut, 15);
		printf(text);
	}
	else 
	{
		SetConsoleTextAttribute(hOut, 15);
		printf(text);
	}

	SetConsoleTextAttribute(hOut, 15);
}

void ConsoleSettings::Log(int x, int y, const char* colour,
	const char* text, bool visibility)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = visibility; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);

	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);

	if (colour == "Blue")
	{
		SetConsoleTextAttribute(hOut, 9);
		printf(text);
	}
	else if (colour == "Green")
	{
		SetConsoleTextAttribute(hOut, 10);
		printf(text);
	}
	else if (colour == "Cyan")
	{
		SetConsoleTextAttribute(hOut, 11);
		printf(text);
	}
	else if (colour == "Red")
	{
		SetConsoleTextAttribute(hOut, 12);
		printf(text);
	}
	else if (colour == "Pink")
	{
		SetConsoleTextAttribute(hOut, 13);
		printf(text);
	}
	else if (colour == "Yellow")
	{
		SetConsoleTextAttribute(hOut, 14);
		printf(text);
	}
	else if (colour == "Black")
	{
		SetConsoleTextAttribute(hOut, 0);
		printf(text);
	}
	else if (colour == "White")
	{
		SetConsoleTextAttribute(hOut, 15);
		printf(text);
	}
	else
	{
		SetConsoleTextAttribute(hOut, 15);
		printf(text);
	}

	SetConsoleTextAttribute(hOut, 15);
}

void ConsoleSettings::Log(posxy* curser, const char* colour,
	const char* text, bool visibility)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = visibility; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);

	COORD coord = { (SHORT)curser->x, (SHORT)curser->y };
	SetConsoleCursorPosition(hOut, coord);

	if (colour == "Blue")
	{
		SetConsoleTextAttribute(hOut, 9);
		printf(text);
	}
	else if (colour == "Green")
	{
		SetConsoleTextAttribute(hOut, 10);
		printf(text);
	}
	else if (colour == "Cyan")
	{
		SetConsoleTextAttribute(hOut, 11);
		printf(text);
	}
	else if (colour == "Red")
	{
		SetConsoleTextAttribute(hOut, 12);
		printf(text);
	}
	else if (colour == "Pink")
	{
		SetConsoleTextAttribute(hOut, 13);
		printf(text);
	}
	else if (colour == "Yellow")
	{
		SetConsoleTextAttribute(hOut, 14);
		printf(text);
	}
	else if (colour == "Black")
	{
		SetConsoleTextAttribute(hOut, 0);
		printf(text);
	}
	else if (colour == "White")
	{
		SetConsoleTextAttribute(hOut, 15);
		printf(text);
	}
	else
	{
		SetConsoleTextAttribute(hOut, 15);
		printf(text);
	}

	SetConsoleTextAttribute(hOut, 15);
}

void ConsoleSettings::ClearConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	setCurser(0, 0, false);
	for (int i = 0; i < rows + 1; i++)
		for (int j = 0; j < columns + 1; j++)
			printf("\x20");
	setCurser(0, 0, false);
}
