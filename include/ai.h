// game.State() (to get state from game) (positions?)
// move (in direction of ball)
// inherit from view
// send ai actions to game (game will call them)

#include <SFML/Graphics.hpp>
#include "game.h"

#ifndef AI_H
#define AI_H

class AI
{
    public:
        void update(sf::Int64);
        Game *game;

        // constructor
        AI(Game&);
};

#endif /* AI_H */