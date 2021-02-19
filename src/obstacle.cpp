#include "obstacle.h"

Obstacle::Obstacle(int x, int y)
{
    this->shape.setPosition(x, y);
    this->shape.setFillColor(sf::Color::White);
}