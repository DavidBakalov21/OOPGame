#include <SFML/Graphics.hpp>
#include <iostream>
class PlayerData {
public:
    std::string PlayerName;
    int Score = 0;
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
            yPos -= 1.3;
        }

    }
    void moveDown() {
        if (yPos < 610) {
            yPos += 1.3;
        }
      
    }
};

class PaddleEnemy : public Paddle {
public:
};

class Ball {
public:
    double xPos=300;
    double yPos=300;
    double Speedy=1;
    double Speedx=1;


    bool collidesWithPlayer(const PaddlePlayer& player) const {
        sf::FloatRect ballBounds(xPos - 30.f, yPos - 30.f, 60.f, 60.f);
        sf::FloatRect playerBounds(50.f, static_cast<float>(player.yPos), 20.f, 90.f);

        return ballBounds.intersects(playerBounds);
    }

    void move(const PaddlePlayer& player, PlayerData& Data) {
        xPos += Speedx;
        yPos += Speedy;
        if (yPos>610 || yPos<0)
        {
            Speedy *= -1;
        }
        if (xPos > 1650) {
            std::cout << "Bot fail";
            Speedx *= -1;
           
        }
        if (xPos < 0)
        {
            std::cout << "Player fail";
            Data.SetScore(-1);
            Speedx *= -1;
        }
        if (collidesWithPlayer(player)) {
            std::cout << "Player hit!" << std::endl;         
            Speedx *= -1; 
            Data.SetScore(1);
        }

    }

    void ChangeSpeed(double XChange, double YChange) {
        Speedx += XChange;
        Speedy += YChange;
    }
};


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
    Renderer(Game& game, Settings& settings, PaddlePlayer& player, Ball& ball, PlayerData& playerData) : game(game), settings(settings), player(player), ball(ball), playerData(playerData) {}

    void handleInput(sf::RenderWindow& window) {
        game.handleInput(window, player);
    }

    void render(sf::RenderWindow& window) {
        window.clear();
        sf::RectangleShape playerPaddle(sf::Vector2f(20.f, 90.f));
        playerPaddle.setPosition(50.f, player.yPos);
        playerPaddle.setFillColor(sf::Color::Green);

        sf::CircleShape Gameball(30.f);
        Gameball.setPosition(ball.xPos, ball.yPos);



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

        window.draw(playerInfoText);

        window.draw(playerPaddle);
        window.draw(Gameball);
        window.display();
    }

private:
    Ball& ball;
    Game& game;
    Settings settings;
    PaddlePlayer& player;
    PlayerData& playerData;
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1700, 700), "Ping pong");
    Game game;
    Settings settings;
    PaddlePlayer player; 
    Ball ball;
    PlayerData playerData;
    Renderer renderer(game, settings, player,ball, playerData);
    while (window.isOpen()) {
        renderer.handleInput(window);
        ball.move(player, playerData);
        renderer.render(window);
    }

    return 0;
}
