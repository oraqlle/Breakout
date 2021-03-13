#include "..\headers\GameEngine.h"
#include "..\headers\StartMenuState.h"

int main()
{
	GameEngine Runtime;
	Runtime.Init(76, 28);
	Runtime.ChangeState(StartMenuState::Instance());

	while (Runtime.Running())
	{
		Runtime.HandleEvents();
		Runtime.Update();
		Runtime.Draw();
	}

	return 0;
}