#include <SFML/Graphics.hpp>

# ifndef OBSTACLE_H
# define OBSTACLE_H

class Obstacle
{
    public:
        sf::RectangleShape shape{sf::Vector2f(20, 20)};

        // constructor
        Obstacle(int, int);
};

# endif /* OBSTACLE_H */