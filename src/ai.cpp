#include "ai.h"

// constructor
AI::AI(Game &gameobj)
{
    this->game = &gameobj;
}

// tells game logic what direction AI wants to go
void AI::update()
{
    auto ballPos = this->game->ball.shape.getPosition();
    auto paddlePos = this->game->aiPaddle.shape.getPosition();

    // move toward ball along the Y axis
    if (ballPos.y > paddlePos.y)
        this->game->aiInput = Down;
    else if (ballPos.y < paddlePos.y)
        this->game->aiInput = Up;
    else
        this->game->aiInput = None;
    ;
};