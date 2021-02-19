#include <SFML/Graphics.hpp>
#include "game.h"

// constructor
Game::Game(sf::RenderWindow &App)
{
    this->app = &App;
}

// calculates the small random perturbation
// 0 is x, 1 is y
float Game::surprise(int axis)
{
    float vel;

    // choose which axis the perturbation is for
    if (axis)
        vel = this->ball.vel.second;
    else
        vel = this->ball.vel.first;

    // decides the range of the perturbation
    // if abs(vel) > 1, then vel * a number between 1 and 0.5
    // otherwise, vel * a number between 1.5 and 1
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

    // reverse ball's x velocity if hits player paddle
    if (playerBounds.intersects(ballBounds))
    {
        // makes sure velocity only flips once when hitting paddle
        if (this->ball.vel.first < 0)
        {
            this->coll = true;
            this->ball.vel.first *= -this->surprise(0);
        }
    }

    // reverse ball's x velocity if hits ai paddle
    else if (aiBounds.intersects(ballBounds))
    {
        // makes sure velocity only flips once when hitting paddle
        if (this->ball.vel.first > 0)
        {
            this->coll = true;
            this->ball.vel.first *= -this->surprise(0);
        }
    }

    float ballRadius{this->ball.shape.getRadius()};
    auto ballPos = this->ball.shape.getPosition();
    auto winSize = this->app->getSize();

    // reverse ball's y velocity if hits top of window
    if ((int) ballPos.y == 0)
    {
        // makes sure velocity only flips once when hitting window border
        if (this->ball.vel.second < 0)
        {
            this->coll = true;
            this->ball.vel.second *= -this->surprise(1);
        }
    }

    // reverse ball's y velocity if hits bottom of window
    if (ballRadius * 2 + (int) ballPos.y == winSize.y)
    {
        // makes sure velocity only flips once when hitting window border
        if (this->ball.vel.second > 0)
        {
            this->coll = true;
            this->ball.vel.second *= -this->surprise(1);
        }
    }

    // ai scores: give points and reset view and logic
    if (ballRadius - (int) ballPos.x == 0)
    {
        this->score.second++;
        this->ball.shape.setPosition(400, 300);
        this->ball.vel = {-0.5, -0.75};
        this->aiScored = true;
    }

    // player scores: give points and reset view and logic
    if (ballRadius + (int) ballPos.x == winSize.x)
    {
        this->score.first++;
        this->ball.shape.setPosition(400, 300);
        this->ball.vel = {-0.5, -0.75};
        this->playerScored = true;
    }

    // ball hits obstacle
    for (int i = 0; i < this->obstacles.size(); i++)
    {
        if (this->obstacles.at(i)->shape.getGlobalBounds().intersects(ballBounds))
        {
            this->coll = true;

            // apply perturbation to x
            this->ball.vel.first *= -this->surprise(0);

            // move the ball an extra pixel so that it double collisions don't occur
            if (this->ball.vel.first > 0)
                this->ball.shape.move(1, 0);
            else
                this->ball.shape.move(-1, 0);

            // apply perturbation to y
            this->ball.vel.second *= -this->surprise(1);

            // move the ball an extra pixel so that it double collisions don't occur
            if (this->ball.vel.second > 0)
                this->ball.shape.move(0, 1);
            else
                this->ball.shape.move(0, -1);
        }
    }
};

// method called from main to update the game logic
void Game::update(sf::Int64 deltaMicro)
{
    // process user input (or lack of)
    // uses deltaMicro to keep number of frame traversed associated with real time, not frames/ticks
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
    // uses deltaMicro to keep number of frame traversed associated with real time, not frames/ticks
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
};

// reset the game logic if game is restarted with 'r'
void Game::restart()
{
    this->playerPaddle.shape.setPosition(50, 270);
    this->aiPaddle.shape.setPosition(750, 270);
    this->ball.shape.setPosition(400, 300);
    this->score = {0, 0};
    this->playerInput = None;
    this->aiInput = None;
    this->coll = false;
    this->playerScored = false;
    this->aiScored = false;
}
