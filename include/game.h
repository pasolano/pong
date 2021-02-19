#include "paddle.h"
#include "ball.h"

#ifndef GAME_H
#define GAME_H

enum direction {Up, Down, Left, Right, None};

class Game
{
    public:
        Paddle playerPaddle{50, 270};
        Paddle aiPaddle{750, 270};
        Ball ball{400, 300};
        std::pair <int, int> score;
        direction playerInput{None};
        direction aiInput{None};
        sf::RenderWindow *app;

        float surprise(int);
        void collision();
        void update(sf::Int64);
        void restart();

        // constructor
        Game(sf::RenderWindow&);
};

#endif /* GAME_H */
