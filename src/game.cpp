#include <SFML/Graphics.hpp>
#include "game.h"
#include <utility>

Game::Game(sf::RenderWindow &App)
{
    this->app = &App;
}

// calculates the small random perturbation
// 0 is x, 1 is y
float Game::surprise(int axis)
{
    float vel;
    if (axis)
        vel = this->ball.vel.second;
    else
        vel = this->ball.vel.first;

    if (vel > 1.f || vel < -1.f)
        return 0.5 + (float) (rand()) / ((float) (RAND_MAX/(0.5)));
    else
        return 1.f + (float) (rand()) / ((float) (RAND_MAX/(0.5)));
}

// dont collide if ball is more than a pixel intersecting with the paddle
void Game::collision()
{
    auto playerBounds = this->playerPaddle.shape.getGlobalBounds();
    auto aiBounds = this->aiPaddle.shape.getGlobalBounds();
    auto ballBounds = this->ball.shape.getGlobalBounds();

    // reverse x velocity if hits paddle
    if (playerBounds.intersects(ballBounds))
    {
        if (this->ball.vel.first < 0)
            this->ball.vel.first *= -this->surprise(0);
        if (this->ball.vel.first > 0)
            this->ball.shape.move(1, 0);
        else
            this->ball.shape.move(-1, 0);
    }

    else if (aiBounds.intersects(ballBounds))
    {
        if (this->ball.vel.first > 0)
            this->ball.vel.first *= -this->surprise(0);
        if (this->ball.vel.first > 0)
            this->ball.shape.move(1, 0);
        else
            this->ball.shape.move(-1, 0);
    }
        

    float ballRadius{this->ball.shape.getRadius()};
    auto ballPos = this->ball.shape.getPosition();
    auto winSize = this->app->getSize();

    // reverse y velocity if hits top or bottom wall
    if (((int) ballPos.y == 0) || (ballRadius * 2 + (int) ballPos.y == winSize.y))
    {
        this->ball.vel.second *= -this->surprise(1);
        if (this->ball.vel.second > 0)
            this->ball.shape.move(0, 1);
        else
            this->ball.shape.move(0, -1);
    }
    // give points if hits left or right wall
    if (ballRadius - (int) ballPos.x == 0)
    {
        this->score.second++;
        this->ball.shape.setPosition(400, 300);
        this->ball.vel = {-0.5, -0.75};
    }

    if (ballRadius + (int) ballPos.x == winSize.x)
    {
        this->score.first++;
        this->ball.shape.setPosition(400, 300);
        this->ball.vel = {-0.5, -0.75};
    }
};

void Game::update(sf::Int64 deltaMicro)
{
    // process user input (or lack of)
    switch(this->playerInput)
    {
        case Up:
            this->playerPaddle.vel.second = -0.001 * deltaMicro;
            break;
        case Down:
            this->playerPaddle.vel.second = 0.001 * deltaMicro;
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
            this->aiPaddle.vel.second = -0.0005 * deltaMicro;
            break;
        case Down:
            // add deltaMs
            this->aiPaddle.vel.second = 0.0005 * deltaMicro;
            break;
        case None:
            this->aiPaddle.vel.second = 0.f;
            break;
    };

    // move shapes
    this->collision();

    this->playerPaddle.shape.move(this->playerPaddle.vel.first, this->playerPaddle.vel.second);
    this->aiPaddle.shape.move(this->aiPaddle.vel.first, this->aiPaddle.vel.second);

    this->ball.shape.move(this->ball.vel.first * 0.001 * deltaMicro, this->ball.vel.second * 0.001 * deltaMicro);
    
    // also make sure paddle can't go past window boundary

    // wait for player input to move the ball
};

void Game::restart()
{
    this->playerPaddle.shape.setPosition(50, 270);
    this->aiPaddle.shape.setPosition(750, 270);
    this->ball.shape.setPosition(400, 300);
    this->score = {0, 0};
    this->playerInput = None;
    this->aiInput = None;
}
