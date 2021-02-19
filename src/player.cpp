#include <string>
#include "player.h"

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

void Player::draw(sf::Drawable &drawable)
{
    this->window->draw(drawable);
};

void Player::drawAll()
{
    this->scoreText.setString( std::to_string(this->game->score.first) + " " + std::to_string(this->game->score.second));
    this->draw(this->scoreText);
    this->draw(this->game->playerPaddle.shape);
    this->draw(this->game->aiPaddle.shape);
    this->draw(this->game->ball.shape);
};

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

void Player::updateView()
{
    auto score = this->game->score;
    if (score.first >= 11)
        this->gameOver(0); // pass who won
    else if (score.second >= 11)
        this->gameOver(1);
    else
        this->drawAll();
};