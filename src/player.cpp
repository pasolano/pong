#include <string>
#include "player.h"

// constructor
Player::Player(sf::RenderWindow &app, Game &gameObj)
{
    this->window = &app;
    this->game = &gameObj;

    // define score
    if (!this->font.loadFromFile("../data/font.ttf"))
    {
        throw "Failed to load font from file";
    }
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(30);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setStyle(sf::Text::Regular);
    this->scoreText.setPosition(10, 10);
    this->scoreText.setString("0 0");
};

// tells game logic the player's inputs
void Player::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->game->playerInput = Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->game->playerInput = Down;
    else
        this->game->playerInput = None;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        this->game->restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        this->window->close();
};

// draws any drawable object to current window
void Player::draw(sf::Drawable &drawable)
{
    this->window->draw(drawable);
};

// calls draw() on all of our objects for the player view
void Player::drawAll()
{
    this->scoreText.setString(std::to_string(this->game->score.first) + " " + std::to_string(this->game->score.second));
    this->draw(this->scoreText);
    this->draw(this->game->playerPaddle.shape);
    this->draw(this->game->aiPaddle.shape);
    this->draw(this->game->ball.shape);
    
    for (int i = 0; i < this->game->obstacles.size(); i++)
    {
        this->draw(this->game->obstacles.at(i)->shape);
    }
};

// draws the message saying who won the game
void Player::gameOver(int whoWon)
{
    sf::Text gameOverMsg;
    gameOverMsg.setFont(this->font);
    gameOverMsg.setCharacterSize(80);
    gameOverMsg.setFillColor(sf::Color::White);
    gameOverMsg.setStyle(sf::Text::Regular);
    gameOverMsg.setPosition(15, 15);

    std::string winner;
    if (whoWon)
        winner = "AI";
    else
        winner = "Player";

    gameOverMsg.setString(winner + " won!\nPress \'r\' to restart\nPress \'q\' to quit");

    this->draw(gameOverMsg);
};

// make sound if the passed flag is true
// game logic owns the flags and changes when collisions occur
void Player::makeSound(std::string filename, bool &flag)
{
    if (flag)
    {
        static sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("../data/" + filename + ".wav"))
            throw "Could not load sound";
        static sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        flag = false;
    }
}

// call sound() on all of our sounds and flags from game logic
void Player::sounds()
{
    this->makeSound("beep", this->game->coll);
    this->makeSound("ping", this->game->playerScored);
    this->makeSound("error", this->game->aiScored);
}

// method that updates entire player view
// called from main loop
void Player::updateView()
{
    auto score = this->game->score;
    if (score.first >= 11)
        this->gameOver(0); // 0 means player won
    else if (score.second >= 11)
        this->gameOver(1); // 1 means AI won
    else
    {
        this->sounds();
        this->drawAll();
    }
};