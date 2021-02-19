#include <SFML/Graphics.hpp>
#include <utility>

#ifndef BALL_H
#define BALL_H

class Ball
{
    public:
        std::pair <float, float> vel{-0.5, -0.75};
        sf::CircleShape shape{10.f};

        // Constructor
        Ball(int, int);
};

#endif /* BALL_H */