#include "..\headers\GameEngine.h"
#include "..\headers\StartMenuState.h"


int main()
{
	values* g_vals = new values{ 00, 00 };

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