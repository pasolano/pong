// inherit from view
// possible sounds in future
// player.cpp uses game.State() to get from it (with positions only maybe)
// send actions inferred from input to game logic

// draw points every tick?
// have one method for drawActor(actor)

#include <SFML/Graphics.hpp>
#include "game.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:
        sf::RenderWindow *window;
        Game *game;

        void update(sf::Int32);
        // void move(direction);
        void draw(sf::Shape&);
        void drawAll(sf::Int64);

        // Constructor
        Player(sf::RenderWindow &app, Game &gameObj);
};

#endif /* PLAYER_H */