#include <SFML/Graphics.hpp>
#include <utility>

#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
    public:
        std::pair <int, int> vel;
        sf::RectangleShape shape{sf::Vector2f(10, 75)};

        // Constructor
        Paddle(int, int);
};

#endif /* PADDLE_H */