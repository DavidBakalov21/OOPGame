#include <SFML/Graphics.hpp>
#include <iostream>
class Paddle {
public:
    double speed;
    double size;
    double xPos;
    double yPos=20;
};

class PaddlePlayer : public Paddle {
public:
    void moveUp() {
        if (yPos > 0) {
            yPos -= 20;
        }

    }
    void moveDown() {
        if (yPos < 610) {
            yPos += 20;
        }
      
    }
};

class PaddleEnemy : public Paddle {
public:
};

class Ball {
public:
    double xPos;
    double yPos;
    double Speedy;
    double Speedx;
    void move() {
        xPos += Speedx;
        yPos += Speedy;
    }

    void ChangeSpeed(double XChange, double YChange) {
        Speedx += XChange;
        Speedy += YChange;
    }
};

class PlayerData {
public:
    std::string PlayerName;
    int Score;
    void SetScore(int score) {
        Score += score;
    }
};

class EnemyData {
public:
    int Score;
    void SetScore(int score) {
        Score += score;
    }
};
class Game {
public:
    Game() {}

    void handleInput(sf::RenderWindow& window, PaddlePlayer& player) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    player.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    player.moveDown();
                }

                else if (event.key.code == sf::Keyboard::B) {
                    window.close();
                }
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
    Renderer(Game& game, Settings& settings, PaddlePlayer& player) : game(game), settings(settings), player(player) {}

    void handleInput(sf::RenderWindow& window) {
        game.handleInput(window, player);
    }

    void render(sf::RenderWindow& window) {
        window.clear();
        sf::RectangleShape playerPaddle(sf::Vector2f(20.f, 90.f));
        playerPaddle.setPosition(50.f, player.yPos);
        playerPaddle.setFillColor(sf::Color::Green);
        window.draw(playerPaddle);
        window.display();
    }

private:
    Game& game;
    Settings settings;
    PaddlePlayer& player;
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1700, 700), "Ping pong");
   // sf::RenderWindow window2(sf::VideoMode(700, 700), "Settings");
    Game game;
    Settings settings;
    PaddlePlayer player; 
    Renderer renderer(game, settings, player);
    while (window.isOpen()) {
        renderer.handleInput(window);
        renderer.render(window);
    }

    return 0;
}
