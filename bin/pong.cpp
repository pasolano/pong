#include <SFML/Graphics.hpp>
#include "ai.h"
#include "game.h"
#include "player.h"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Pong", sf::Style::Close);

  sf::Clock delta;
  sf::Time dt;
  Game game(App);
  Player player(App, game);
  AI ai(game);
  bool paused = false;

  // start main loop
  while(App.isOpen())
  {
    // clear player view
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

        // Pause Game
        case(sf::Event::LostFocus):
          paused = true;
          break;

        // Unpause Game
        case(sf::Event::GainedFocus):
          paused = false;
          break;
      }
    }

    // get time elapsed
    dt = delta.restart();
    sf::Int64 deltaMicro = dt.asMicroseconds();

    // update game logic if the game is in focus
    if(!paused)
    {
      player.update();
      ai.update();
      game.update(deltaMicro);
    }

    // update what the player sees
    player.updateView();

    // display
    App.display();
  }

  // Done.
  return 0;
}
