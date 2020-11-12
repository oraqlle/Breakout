#include "GameManager.h"

int main()
{
	GameManager* Runtime;
	Runtime = new GameManager(76, 28);
	Runtime->Run();
	//Runtime->PrintTest();

	delete Runtime;

	return 0;
}