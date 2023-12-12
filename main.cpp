#include <SFML/Graphics.hpp>




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



class PaddlePlayer:Paddle {
public:


};

class PaddleEnemy :Paddle {
public:


};

class Ball {
public:
    double xPos;
    double yPos;
    double Speedy;
    double Speedx;
};

class PlayerData {
public:
    std::string PlayerName;
    std::string Score;
};
class EnemyData {
public:
    std::string Score;
};
class Settings {
public:
    double ballSpeedY;
    double ballSpeedX;
    double PaddleESize;
    double paddleSize;
    double PaddleESpeed;
    double PaddleSpeed;
};

class Renderer {
public:
    Renderer(Game& game) : game(game) {}

    void render(sf::RenderWindow& window) {
        window.clear();
        sf::RectangleShape rectangle(sf::Vector2f(20.f, 90.f));
        rectangle.setPosition(50.f, 275.f);
        rectangle.setFillColor(sf::Color::Green);
        window.draw(rectangle);

        window.display();
    }

private:
    Game& game;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1700, 700), "Ping pong");
    Game game;
    Renderer renderer(game);
    while (window.isOpen()) {
        game.handleInput(window);
        renderer.render(window);
    }

    return 0;
}