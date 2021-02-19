#include <SFML/Graphics.hpp>
#include "game.h"
#include <utility>
#include <iostream>

Game::Game(sf::RenderWindow &App)
{
    this->app = &App;
}

void Game::collision()
{
    auto playerBounds = this->playerPaddle.shape.getGlobalBounds();
    auto aiBounds = this->aiPaddle.shape.getGlobalBounds();
    auto ballBounds = this->ball.shape.getGlobalBounds();

    // reverse x velocity if hits paddle
    if (playerBounds.intersects(ballBounds) || aiBounds.intersects(ballBounds))
        this->ball.vel.first *= -1;

    float ballRadius{this->ball.shape.getRadius()};
    auto ballPos = this->ball.shape.getPosition();
    auto winSize = this->app->getSize();

    // reverse y velocity if hits top or bottom wall
    if ((ballPos.y == 0) || (ballRadius * 2 + ballPos.y == winSize.y))
        this->ball.vel.second *= -1;

    // give points if hits left or right wall
    if (ballRadius - ballPos.x == 0)
    {
        this->score.second++;
        this->ball.shape.setPosition(400, 300);
    }

    if (ballRadius + ballPos.x == winSize.x)
    {
        this->score.second++;
        this->ball.shape.setPosition(400, 300);
    }
};

int count = 0;

void Game::update(sf::Int64 deltaMs)
{
    // process user input (or lack of)
    switch(this->playerInput)
    {
        case Up:
            // add deltaMs
            this->playerPaddle.vel.second = -1.f;
            break;
        case Down:
            // add deltaMs
            this->playerPaddle.vel.second = 1.f;
            break;
        case None:
            this->playerPaddle.vel.second = 0.f;
            break;
    };

    // process ai input (or lack of)
    switch(this->aiInput)
    {
        case Up:
            // add deltaMs
            this->aiPaddle.vel.second = -1.f;
            break;
        case Down:
            // add deltaMs
            this->aiPaddle.vel.second = 1.f;
            break;
        case None:
            this->aiPaddle.vel.second = 0.f;
            break;
    };

    // move shapes
    if (count % 10 == 0)
    {
        this->collision(); // hacky way of keeping vel from flipping multiple timess during one collision
        this->playerPaddle.shape.move(this->playerPaddle.vel.first, this->playerPaddle.vel.second);
        this->aiPaddle.shape.move(this->aiPaddle.vel.first, this->aiPaddle.vel.second);
    }
    if (count % 30 == 0)
        this->ball.shape.move(this->ball.vel.first, this->ball.vel.second);
    count++;
    // check for collision. if so, change ball velocity or reset position and assign points
    // move ball position x velX * deltaMs
    // move ball position y velY * deltaMs
    // if view says to, move player or ai paddle vel*deltaMs


    // also make sure paddle can't go past window boundary

    // wait for player input to move the ball
};

void Game::restart()
{
    this->playerPaddle.shape.setPosition(50, 270);
    this->aiPaddle.shape.setPosition(750, 270);
    this->ball.shape.setPosition(400, 300);
    this->score.first = 0;
    this->score.second = 0;
    this->playerInput = None;
    this->aiInput = None;
}
