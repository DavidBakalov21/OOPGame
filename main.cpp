#include <SFML/Graphics.hpp>
#include <iostream>
#include "PaddlePlayer.h"
#include "PaddleEnemy.h"
#include "Ball.h"
#include "PlayerData.h"
#include "EnemyData.h"
#include <SFML/Window.hpp>

class Game {
public:
    Game() {}

    void handleInput(sf::RenderWindow& window, PaddlePlayer& player) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.moveUp();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.moveDown();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                window.close();
            }
        }
    }
};

class VictoryScreen {
public:
    VictoryScreen(const std::string& winner) : winner(winner) {}

    void handleInput(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }

    void render(sf::RenderWindow& window) {
        window.clear();
        font.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\Arial.ttf");
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(850.f, 300.f);
        text.setString(winner + " wins! Press ESC to exit.");

        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\bg.png");
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setPosition(0.f, 0.f);
        backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width,
            static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height);

        window.draw(backgroundSprite);
        window.draw(text);
        window.display();
    }

private:
    sf::Text text;
    sf::Font font;
    std::string winner;
};



class Renderer {
public:
    Renderer(Game& game, PaddlePlayer& player, Ball& ball, PlayerData& playerData, EnemyData& enemyData, PaddleEnemy& enemyPaddle)
        : game(game),  player(player), ball(ball), playerData(playerData), enemyData(enemyData), enemyPaddle(enemyPaddle) {}

    void handleInput(sf::RenderWindow& window) {
        game.handleInput(window, player);
    }
    void render(sf::RenderWindow& window) {
        window.clear();
        sf::RectangleShape playerPaddle(sf::Vector2f(20.f, 90.f));
        playerPaddle.setPosition(15.f, player.yPos);
        playerPaddle.setFillColor(sf::Color::Green);
        sf::RectangleShape EnemyPaddle(sf::Vector2f(20.f, 130.f));
        EnemyPaddle.setPosition(1655.f, enemyPaddle.yPos);
        EnemyPaddle.setFillColor(sf::Color::Red);
        sf::CircleShape Gameball(ball.radius);
        Gameball.setPosition(ball.xPos, ball.yPos);
        sf::Texture textureBall;
       textureBall.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\ball.png");
       Gameball.setTexture(&textureBall);
        sf::Font font;
        font.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\Arial.ttf");
        sf::Text playerInfoText;
        playerInfoText.setFont(font);
        playerInfoText.setCharacterSize(20);
        playerInfoText.setFillColor(sf::Color::White);
        playerInfoText.setPosition(10.f, 10.f);
        playerInfoText.setString("Player: Score: " + std::to_string(playerData.Score));
        sf::Text EnemyInfoText;
        EnemyInfoText.setFont(font);
        EnemyInfoText.setCharacterSize(20);
        EnemyInfoText.setFillColor(sf::Color::White);
        EnemyInfoText.setPosition(1500.f, 10.f);
        EnemyInfoText.setString("Bot Score:" + std::to_string(enemyData.Score));
       sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\bg.png");
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setPosition(0.f, 0.f);
        backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width,
            static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height);

        window.draw(backgroundSprite);
        window.draw(EnemyInfoText);
        window.draw(playerInfoText);
        window.draw(playerPaddle);
        window.draw(Gameball);
        window.draw(EnemyPaddle);
        window.display();

       
    }
private:
    Ball& ball;
    Game& game;
    EnemyData& enemyData;
    PaddlePlayer& player;
    PlayerData& playerData;
    PaddleEnemy& enemyPaddle;
};
int main() {
    bool gameStarted = false;
    sf::RenderWindow window(sf::VideoMode(1700, 700), "Ping pong");
  
    Game game;
    PaddlePlayer player;
    Ball ball;
    PlayerData playerData;
    EnemyData enemy;
    PaddleEnemy enemyPaddle;
    Renderer renderer(game,  player, ball, playerData, enemy, enemyPaddle);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
       float dt = elapsed.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !gameStarted) {
            gameStarted = true; 
        }
        if (gameStarted)
        {
            renderer.handleInput(window);
            enemyPaddle.moveTowardsPredictedPosition(ball);
            ball.move(player, playerData, enemy, dt, enemyPaddle);
           
        }
        if (playerData.Score < 15 && enemy.Score < 15) {
            renderer.render(window);
        }
        else if (playerData.Score >= 15) {
            VictoryScreen victoryScreen("Player");
            while (window.isOpen()) {
                victoryScreen.handleInput(window);
                victoryScreen.render(window);
            }
        }
        else if (enemy.Score >= 15) {
            VictoryScreen victoryScreen("Enemy");
            while (window.isOpen()) {
                victoryScreen.handleInput(window);
                victoryScreen.render(window);
            }
        } 
    }
    return 0;
}