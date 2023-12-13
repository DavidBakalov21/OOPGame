#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
public:
    Game() {}

    void handleInput(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

private:
};

class Paddle {
public:
    double speed;
    double size;
    double xPos;
    double yPos;
};

class PaddlePlayer : public Paddle {
public:
    void moveDown() {
        yPos=-speed;
    }
    void moveUp() {
        yPos =+speed;
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
    Renderer(Game& game, Settings& settings) : game(game), settings(settings) {}

    void handleInput(sf::RenderWindow& window) {
        game.handleInput(window);
    }

    void render(sf::RenderWindow& window) {
        window.clear();

        // Render game elements
        sf::RectangleShape rectangle(sf::Vector2f(20.f, 90.f));
        rectangle.setPosition(50.f, 275.f);
        rectangle.setFillColor(sf::Color::Green);
        window.draw(rectangle);

        // Render settings UI
       

        window.display();
    }

private:
    Game& game;
    Settings settings;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1700, 700), "Ping pong");
    Game game;
    Settings settings;
    Renderer renderer(game, settings);
    while (window.isOpen()) {
        renderer.handleInput(window);
        renderer.render(window);
    }

    return 0;
}