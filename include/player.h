#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
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
        void makeSound(std::string, bool&);
        void sounds();
        void gameOver(int);
        void updateView();

        // Constructor
        Player(sf::RenderWindow &app, Game &gameObj);
};

#endif /* PLAYER_H */