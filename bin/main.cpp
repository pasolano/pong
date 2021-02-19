#include <SFML/Graphics.hpp>
#include "ai.h"
#include "ball.h"
#include "game.h"
#include "paddle.h"
#include "player.h"
#include <iostream>
#include <utility>

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Pong", sf::Style::Close);

  sf::Clock delta;
  sf::Time dt;
  Game game(App);
  Player player(App, game);
  AI ai(game);

  // start main loop
  while(App.isOpen())
  {
    App.clear();
    // process events
    sf::Event Event;
    // while there are pending events
    while(App.pollEvent(Event))
    {
      switch (Event.type)
      {
        // Exit
        case(sf::Event::Closed):
          App.close();
          break;
      }
    }
    // get time elapsed
      dt = delta.restart();
      sf::Int64 deltaMs = dt.asMicroseconds();

      // HOW TO MAKE SURE PLAYER VIEW HAS MOST RECENT GRAPHICS BUT GAME HAS MOST RECENT INPUTS
      player.update(deltaMs);
      ai.update(deltaMs);
      game.update(deltaMs);
      player.updateView();

      // display
      App.display();
  }

  // Done.
  return 0;
}
