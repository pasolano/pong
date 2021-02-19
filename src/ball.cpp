#include "ball.h"
#include <iostream>

Ball::Ball(int x, int y)
{
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(x, y);
}