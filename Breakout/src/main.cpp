#include "..\headers\GameManager.h"

int main()
{
	GameManager Runtime(76, 28);
	int current = Runtime.Run();

	return current;
}