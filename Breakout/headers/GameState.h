#pragma once

#include "GameEngine.h"
#include "val.h"

class GameState
{
protected:
    GameState() { }

public:
    virtual void Init(DIM* _dim) = 0;
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