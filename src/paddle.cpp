#include "paddle.h"

Paddle::Paddle(int x, int y)
{
    this->shape.setPosition(x, y);
    this->shape.setFillColor(sf::Color::White);
}