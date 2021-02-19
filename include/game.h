#include "paddle.h"
#include "ball.h"
#include "obstacle.h"

#ifndef GAME_H
#define GAME_H

enum direction {Up, Down, Left, Right, None};

class Game
{
    public:
        Paddle playerPaddle{50, 270};
        Paddle aiPaddle{750, 270};
        Ball ball{400, 300};

        // make obstacles
        Obstacle obstacle1{200, 150};
        Obstacle obstacle2{600, 150};
        Obstacle obstacle3{200, 450};
        Obstacle obstacle4{600, 450};
        std::vector <Obstacle*> obstacles{&obstacle1, &obstacle2, &obstacle3, &obstacle4};

        std::pair <int, int> score;
        direction playerInput{None};
        direction aiInput{None};
        bool coll{false};
        bool playerScored{false};
        bool aiScored{false};
        sf::RenderWindow *app;

        float surprise(int);
        void collision();
        void update(sf::Int64);
        void restart();

        // constructor
        Game(sf::RenderWindow&);
};

#endif /* GAME_H */
