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
        std::pair <float, float> score;
        direction playerInput{None};
        direction aiInput{None};
        sf::RenderWindow *app;

        void collision();
        void update(sf::Int64);

        // constructor
        Game(sf::RenderWindow&);
};

#endif /* GAME_H */
