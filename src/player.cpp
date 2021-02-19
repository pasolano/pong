#include <iostream>
#include "player.h"

Player::Player(sf::RenderWindow &app, Game &gameObj)
{
    this->window = &app;
    this->game = &gameObj;
};

void Player::update(sf::Int32 deltaMs)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->game->playerInput = Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->game->playerInput = Down;
    }
    else
    {
        this->game->playerInput = None;
    }
}

void Player::draw(sf::Shape &shape)
{
    this->window->draw(shape);
};

void Player::drawAll(sf::Int64 deltaMs)
{
    // TODO draw points (here so other features get drawn on top)
    this->draw(this->game->playerPaddle.shape);
    this->draw(this->game->aiPaddle.shape);
    this->draw(this->game->ball.shape);
};