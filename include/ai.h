#include <SFML/Graphics.hpp>
#include "game.h"

#ifndef AI_H
#define AI_H

class AI
{
    public:
        void update();
        Game *game;

        // constructor
        AI(Game&);
};

#endif /* AI_H */