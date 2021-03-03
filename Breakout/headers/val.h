#pragma once
#include "..\include\include.h"

typedef struct DIM
{
	core::rectangle<int>* _Screen;
	core::rectangle<int>* _Border;
	core::rectangle<int>* _Gameboard;
};

typedef struct BUFF
{
	core::Matrix<char>* Screen;
	core::Matrix<char>* Border;
	core::Matrix<char>* GameBuff;
};

typedef struct FNAMES
{
	cstring nTitle;
	cstring nTemp;
	cstring nBaselevel;
	cstring nLevel_1;
	cstring nHighScore;
};

typedef struct FILES
{
	FILE* fTitle;
	FILE* fTemp;
	FILE* fBaseLevel;
	FILE* fLevel_1;
	FILE* fHighScore;
};

typedef struct TEXTPOS
{
	core::posxy* _null;
	core::posxy* _endline;
	core::posxy* _midpoint;

	core::posxy* _Title;
	core::posxy* _ScorePos;

	core::posxy* _PlayerStart;
	core::posxy* _BallStart;
	core::posxy* _StartText;
	core::posxy* _BricksStart;
};