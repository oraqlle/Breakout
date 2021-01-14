#include "..\headers\GameManager.h"

int main()
{
	GameManager Runtime(76, 28);
	Runtime.Run();

	xcon::pause();

	return 0;
}