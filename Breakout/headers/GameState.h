#pragma once

#include "GameEngine.h"
#include "StartMenuState.h"
#include "ControlMenuState.h"
#include "LeaderboardMenuState.h"
#include "PauseMenuState.h"
#include "MainGameState.h"
#include "QuitState.h"

class GameState
{
protected:
    GameState() { }

public:
    virtual void Init(GameEngine* engine) = 0;
    virtual void CleanUp() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents(GameEngine* engine) = 0;
    virtual void Update(GameEngine* engine) = 0;
    virtual void Draw(GameEngine* engine) = 0;

    void ChangeState(GameEngine* engine, 
        GameState* state) 
    { engine->ChangeState(state); }
};