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
        sf::Text scoreText;
        sf::Font font;

        void update();
        void draw(sf::Drawable&);
        void drawAll();
        void gameOver(int);
        void updateView();

        // Constructor
        Player(sf::RenderWindow &app, Game &gameObj);
};

#endif /* PLAYER_H */