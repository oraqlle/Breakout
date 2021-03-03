#include "..\headers\Runtime.h"


// Constructor
Runtime::Runtime(int _w, int _h)
	:  w(_w), h(_h)
{ }


// Destructor
Runtime::~Runtime()
{
	delete engine;
}


// Main Runtime method
int Runtime::Run()
{
	xcon::clear_console();

	engine->Init(w, h);
	engine->ChangeState(MenuState::Instance());

	while (engine->Running())
	{
		/*if (!init)
			_Init_();*/

		engine->HandleEvents();
		engine->Update();
		engine->Draw();
	}

	// Eventually, load in a Gameover screen
	xcon::clear_console();

	return 0;
}