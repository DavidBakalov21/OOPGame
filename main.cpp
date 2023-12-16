#include <SFML/Graphics.hpp>
#include <iostream>
#include "PaddlePlayer.h"
#include "PaddleEnemy.h"
#include "Ball.h"
#include "PlayerData.h"
#include "EnemyData.h"
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



class Settings {
public:


    void setParameters(double NewSpeedX, double NewSpeedY, double NewSize, double NewESize, double NewPlayerSpeed, double NewEnemySpeed) {
        ballSpeedX = NewSpeedX;
        ballSpeedY = NewSpeedY;
        PaddleESize = NewESize;
        paddleSize = NewSize;
        PaddleESpeed = NewEnemySpeed;
        PaddleSpeed = NewPlayerSpeed;
    }
private:
    double ballSpeedY;
    double ballSpeedX;
    double PaddleESize;
    double paddleSize;
    double PaddleESpeed;
    double PaddleSpeed;
};

class Renderer {
public:
    Renderer(Game& game, Settings& settings, PaddlePlayer& player, Ball& ball, PlayerData& playerData, EnemyData& enemyData, PaddleEnemy& enemyPaddle)
        : game(game), settings(settings), player(player), ball(ball), playerData(playerData), enemyData(enemyData), enemyPaddle(enemyPaddle) {}

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
        if (textureBall.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\ball.png")) {
            Gameball.setTexture(&textureBall);
        }


        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\Давід\\source\\repos\\OOPGame\\x64\\Debug\\Arial.ttf")) {
            return;
        }

        sf::Text playerInfoText;
        playerInfoText.setFont(font);
        playerInfoText.setCharacterSize(20);
        playerInfoText.setFillColor(sf::Color::White);
        playerInfoText.setPosition(10.f, 10.f);
        playerInfoText.setString("Player: " + playerData.PlayerName + " Score: " + std::to_string(playerData.Score));





        sf::Text EnemyInfoText;
        EnemyInfoText.setFont(font);
        EnemyInfoText.setCharacterSize(20);
        EnemyInfoText.setFillColor(sf::Color::White);
        EnemyInfoText.setPosition(1450.f, 10.f);
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
    Settings settings;
    EnemyData& enemyData;
    PaddlePlayer& player;
    PlayerData& playerData;
    PaddleEnemy& enemyPaddle;
};


int main() {
    bool gameStarted = false;
    sf::RenderWindow window(sf::VideoMode(1700, 700), "Ping pong");
  
    Game game;
    Settings settings;
    PaddlePlayer player;
    Ball ball;
    PlayerData playerData;
    EnemyData enemy;
    PaddleEnemy enemyPaddle;
    Renderer renderer(game, settings, player, ball, playerData, enemy, enemyPaddle);
    sf::Clock clock;
    sf::Clock predictionClock;
    float dt = 0.0f;

    
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        dt = elapsed.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !gameStarted) {
            gameStarted = true; 
        }
        if (gameStarted)
        {
            renderer.handleInput(window);
            enemyPaddle.moveTowardsPredictedPosition(ball);
            ball.move(player, playerData, enemy, dt, enemyPaddle);
           
        }
        renderer.render(window);
      
    }

    return 0;
}