#include "../headers/GameEngine.h"
#include "../headers/GameState.h"
#include "../headers/MainGameState.h"
#include "../headers/PauseMenuState.h"
#include "../headers/QuitState.h"

MainGameState MainGameState::m_MainGameState;

void MainGameState::Init(GameEngine* engine)
{
	w = engine->game_dim->w;
	h = engine->game_dim->h;

	s_w = engine->screen_dim->h;
	s_h = engine->screen_dim->h;

	text_offset = w + 5;

	// scores
	p_score = &engine->g_vars->g_score;
	p_highscore = &engine->g_vars->g_highscore;

	//Init checks
	init = false;
	border_init = false;

	_Border = new core::rectangle<int>{ w, h };
	_Gameboard = new core::rectangle<int>{ (w - 3), (h - 2) };
	_Bricks = new core::rectangle<int>{ (_Border->w - 5), (_Border->h - 19) };


	// Ball and Player Positions
	_PlayerStart = new core::posxy{ ((_Gameboard->w / 2) - 13), (_Gameboard->h - 3) };
	_BallStart = new core::posxy{ (_Gameboard->w / 2), (_Gameboard->h - 6) };
	_StartText = new core::posxy{ text_offset, ((_Gameboard->h / 2) - 9) };
	_BricksStart = new core::posxy{ 2, 2 };

	// Base Positions
	_null = new core::posxy{ 0, 0 };
	g_endline = new core::posxy{ 0, (_Border->h + 1) };
	g_midpoint = new core::posxy{ (w / 2), (h / 2) };
	s_midpoint = new core::posxy{ (s_w / 2), (s_h / 2) };

	// Start Menu Text Positions
	_Title = new core::posxy{ 4, 3 };

	// Text Positions
	_ScorePos = new core::posxy{ text_offset, ((_Gameboard->h / 2) - 10) };

	//File Names - "C:\Dev\MyGames\Breakout\Breakout\disc\title.txt"
	nTitle = "./disc/title.txt";
	nTemp = "./disc/temp.txt";
	nBaselevel = "./disc/Base_Layout.txt";
	nLevel_1 = "./disc/Level_1.txt";
	nHighScore = "./disc/HighScore.txt";


	// External Objects
	ball = new Ball(_BallStart);
	player = new Paddle(_PlayerStart);
	//fstream = new FileStream(Buffer);

	Border = new core::Matrix<char>(w, h);
	GameBuff = new core::Matrix<char>(_Gameboard->w, _Gameboard->h);
	EntryBuff = new core::Matrix<char>(_Gameboard->w, _Gameboard->h);
	Bricks = new core::Matrix<char>(_Bricks->w, _Border->h);
}

MainGameState::~MainGameState()
{
	delete ball, player, Border, GameBuff, EntryBuff, Bricks, _Border, _Gameboard,
		_Bricks, _PlayerStart, _BallStart, _StartText, _BricksStart, _Title, _ScorePos;
}

void MainGameState::CleanUp()
{
	init = false;
	border_init = false;

	ball->Reset();
	player->Reset();

	Border->fill('\x20');
	GameBuff->fill('\x20');
	EntryBuff->fill('\x20');
	Bricks->fill('\x20');

	*p_score = 0;
	xcon::clear_console();
}

void MainGameState::Pause()
{

}

void MainGameState::Resume()
{

}

void MainGameState::HandleEvents(GameEngine* engine)
{
	Input(engine);
}

void MainGameState::Update(GameEngine* engine)
{
	Logic(engine);
}

void MainGameState::Draw(GameEngine* engine)
{
	if (!init)
	{
		_Init_();
		xcon::console_print(*_StartText, GREEN, "Press 'Space' to Start");
		_Init_Print();
	}
	else
	{
		PrintGame();
	}
}


void MainGameState::ScoreUp()
{
	*p_score += 10;
	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", *p_score, highscore);
	HighScore(*p_score);
}

// Highscore Tracker
void MainGameState::HighScore(
	int& _score
)
{
	_score > highscore ? highscore = _score : NULL;
}


// Checks Buffer if their are Bricks at the Ball's location
void MainGameState::BrickCollision(
	int& _ballX,
	int& _ballY
)
{
	for (int i = 0; i < _Gameboard->h; i++)
		for (int j = 0; j < _Gameboard->w; j++)
		{
			char _val = GameBuff->get(j, i);
			if ((_val == '#') && (_ballX == j && _ballY == i))
			{
				GameBuff->set(j, i, '\x20');
				Bricks->set(j, i, '\x20');
				ScoreUp();
				ball->randomDir();
			}
		}
}

// Checks if the ball has collided with the paddle
void MainGameState::PaddleCollision(
	int& _ballX,
	int& _ballY,
	int& _playerX,
	int& _playerY
)
{
	for (int i = 0; i < 26; i++)
		if (_ballY == _playerY - 1)
			if (_ballX == _playerX + i)
			{
				core::eDir dir = ball->getDirection();
				switch (dir)
				{
				case core::eDir::DOWNLEFT:
					ball->chanegDir(core::eDir::UPLEFT);
					break;

				case core::eDir::DOWNRIGHT:
					ball->chanegDir(core::eDir::UPRIGHT);
					break;

				case core::eDir::DOWN:
					ball->chanegDir((core::eDir)((rand() % 3) + 1));
					break;

				default:
					break;
				}
			}
}

// User Input
void MainGameState::Input(GameEngine* engine)
{
	ball->Move();

	int BallX = ball->getX();
	int BallY = ball->getY();

	int PlayerX = player->getX();
	int PlayerY = player->getY();


	while (_kbhit())
	{

		while (!init)
		{
			char current = _getch();

			if ((current == '\x20') && (ball->getDirection() == core::eDir::STOP))
			{
				ball->chanegDir(core::eDir::DOWN);
				ball->Move();
				init = true;
				xcon::console_print(*_StartText, BLACK, "Press 'Space' to Start");
			}
			else
				current = _getch();
		}

		char current = _getch();

		/*while (!init)
		{

			if ((current == '\x20') && (ball->getDirection() == core::eDir::STOP))
			{
				ball->chanegDir(core::eDir::DOWN);
				ball->Move();
				init = true;
				xcon::console_print(*_StartText, BLACK, "Press 'Space' to Start");
			}
		}*/

		if (current == 'a' || current == 'A')
			if (PlayerX > 0)
				player->moveLeft();

		if (current == 'd' || current == 'D')
			if (PlayerX + 26 < _Gameboard->w)
				player->moveRight();

		if (ball->getDirection() == core::eDir::STOP)
		{
			ball->chanegDir(core::eDir::DOWN);
			ball->Move();
		}

		if (current == 'q' || current == 'Q')
		{
			engine->ChangeState(QuitState::Instance());
		}

		if (current == 'e' || current == 'E')
		{
			border_init = false;
			engine->PushState(PauseMenuState::Instance());
		}
	}
}


// Basic Logic for collisions
void MainGameState::Logic(GameEngine* engine)
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	// Paddle Collison
	PaddleCollision(ballX, ballY, playerX, playerY);

	// Brick Collisions
	BrickCollision(ballX, ballY);

	// Bottom wall collision
	if (ballY == _Gameboard->h)
	{
		engine->ChangeState(QuitState::Instance());
	}

	// Top wall collision
	if (ballY == 0)
		ball->chanegDir(ball->getDirection() == core::eDir::UPRIGHT ? core::eDir::DOWNRIGHT : core::eDir::DOWNLEFT);

	// Right wall collision
	if (ballX == _Gameboard->w - 1)
		ball->chanegDir(ball->getDirection() == core::eDir::UPRIGHT ? core::eDir::UPLEFT : core::eDir::DOWNLEFT);

	// Left wall collision
	if (ballX == (_Gameboard->w + 1) - _Gameboard->w)
		ball->chanegDir(ball->getDirection() == core::eDir::UPLEFT ? core::eDir::UPRIGHT : core::eDir::DOWNRIGHT);
}


void MainGameState::CreateBorder()
{
	int temp = Border->fill('\x20');

	for (int column = 0; column < (_Border->w - 1); column++)
	{
		Border->set(column, 0, '\xB2');
	}

	for (int row = 0; row < _Border->h; row++)
	{
		for (int column = 0; column < (_Border->w - 1); column++)
		{
			if (column == 0)
			{
				Border->set(0, row, '\xB2');
			}

			if (column == (_Border->w - 2))
			{
				Border->set(column, row, '\xB2');
				int offset = column + 1;
				Border->set(offset, row, '\n');
			}
		}
	}

	for (int column = 0; column < (_Border->w - 1); column++)
	{
		Border->set(column, (_Border->h - 1), '\xB2');
	}
}


void MainGameState::ClearBuffer(core::Matrix<char>* buff, core::rectangle<int>* _size)
{
	for (int row = 0; row < _size->h; row++)
		for (int column = 0; column < _size->w; column++)
			buff->set(column, row, '\x20');
}


void MainGameState::CreateBricks()
{
	int temp = Bricks->fill('\x20');

	for (int i = 1; i < _Bricks->h; i++)
		for (int j = 2; j < _Bricks->w; j++)
			Bricks->set(j, i, '#');
}


void MainGameState::CopyBricks(core::Matrix<char>* buff)
{
	for (int i = 1; i < _Bricks->h; i++)
		for (int j = 2; j < _Bricks->w; j++)
			if (Bricks->get(j, i) == '#')
				buff->set(j, i, Bricks->get(j, i));
}


void MainGameState::LoadEntities()
{
	int ballX = ball->getX();
	int ballY = ball->getY();

	int playerX = player->getX();
	int playerY = player->getY();

	for (int i = 0; i < _Gameboard->h; i++)
	{
		for (int j = 0; j < _Gameboard->w; j++)
		{
			if (ballX == j && ballY == i)
				GameBuff->set(j, i, 'O');
			else if (GameBuff->get(j, i) == '#')
				continue;
			else
				GameBuff->set(j, i, '\x20');


			for (int Itr = 0; Itr < 26; Itr++)
			{
				if ((j == (playerX + Itr)) && (playerY == i))
					GameBuff->set(j, playerY, '\xDB');
			}
		}
	}
}


void MainGameState::_Init_Print()
{
	if (!border_init)
	{
		xcon::set_curser(*_null);
		int temp1 = Border->print("%c");
		border_init = true;
	}

	CopyBricks(EntryBuff);
	PrintGameBoard(EntryBuff);
	//ClearBuffer(EntryBuff, _Gameboard);

	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", *p_score, highscore);
}


void MainGameState::PrintGameBoard(core::Matrix<char>* buff)
{
	LoadEntities();

	if (!border_init)
	{
		xcon::set_curser(*_null);
		int temp1 = Border->print("%c");
		border_init = true;
	}

	for (int row = 0; row < _Gameboard->h; row++)
	{
		xcon::set_curser(1, (row + 1), false);
		for (int column = 0; column < _Gameboard->w; column++)
		{
			char z = buff->get(column, row);

			if (z == '#')
				xcon::f_console_print(PINK, "%c", z);
			else if (z == 'O')
				xcon::f_console_print(GREEN, "%c", z);
			else
				xcon::f_console_print(WHITE, "%c", z);
		}
	}
}


void MainGameState::PrintGame()
{

	CopyBricks(GameBuff);
	PrintGameBoard(GameBuff);
	//ClearBuffer(GameBuff, _Gameboard);

	xcon::f_console_print(*_ScorePos, BLUE, "Score: %d | High Score: %d", *p_score, highscore);
}


//void MainGameState::GameWindow()
//{
//	if (!init)
//	{
//		xcon::console_print(*_StartText, GREEN, "Press 'Space' to Start");
//		_Init_Print();
//		Input();
//		Logic();
//	}
//	else
//	{
//		PrintGame();
//		Input();
//		Logic();
//	}
//}

void MainGameState::_Init_()
{
	Border->fill('\x20');
	GameBuff->fill('\x20');
	EntryBuff->fill('\x20');
	Bricks->fill('\x20');

	CreateBorder();
	CreateBricks();
}