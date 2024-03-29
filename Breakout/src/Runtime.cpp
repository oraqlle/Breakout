#include "..\headers\Runtime.h"
#include "..\headers\StartMenuState.h"


// Constructor
Runtime::Runtime(int _w, int _h)
	:  w(_w), h(_h), engine()
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
	engine->ChangeState(StartMenuState::Instance());

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