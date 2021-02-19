#include "ai.h"

AI::AI(Game &gameobj)
{
    this->game = &gameobj;
}

void AI::update(sf::Int64 deltaMs)
{
    auto ballPos = this->game->ball.shape.getPosition();
    auto paddlePos = this->game->aiPaddle.shape.getPosition();

    if (ballPos.y > paddlePos.y)
    {
        this->game->aiInput = Down;
    }
    else if (ballPos.y < paddlePos.y)
        this->game->aiInput = Up;
    else
        this->game->aiInput = None;
    // get y position of ball
    // if yball > yaipaddle, make velocity for paddle positive
    // " < " negative
    // " == " 0
    ;
};