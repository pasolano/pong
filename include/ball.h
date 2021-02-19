#include <SFML/Graphics.hpp>
#include <utility>

#ifndef BALL_H
#define BALL_H

class Ball
{
    public:
        std::pair <int, int> vel{-2, -1};
        sf::CircleShape shape{10.f};

        // Constructor
        Ball(int, int);
};

#endif /* BALL_H */