#include "..\headers\Log.h"

void pause(void)
{
	int temp = getchar();
	while (getchar() != '\n')
		temp = getchar();
}

int main(void)
{
	Log("%d\n", 123);
	Log("%s", "Hello World\n");
	Log("%d %s %ls", 123, "Hello", L"World\n");

	pause();
	return 0;
}