#include "Ball.h"
#include "PaddlePlayer.h"
#include "PaddleEnemy.h"
#include "PlayerData.h"
#include "EnemyData.h"
#include <iostream>
#include <SFML/Graphics.hpp> 
bool Ball::collidesWithPlayer(const PaddlePlayer& player, float dt) const {
    sf::Vector2f ballPos(xPos, yPos);
    sf::Vector2f nextBallPos(xPos + Speedx * dt, yPos + Speedy * dt);
    sf::FloatRect currentBallBounds(ballPos.x - radius, ballPos.y - radius, 2 * radius, 2 * radius);
    sf::FloatRect nextBallBounds(nextBallPos.x - radius, nextBallPos.y - radius, 2 * radius, 2 * radius);
    sf::FloatRect playerBounds(50.f, static_cast<float>(player.yPos), 20.f, 90.f);

    return nextBallBounds.intersects(playerBounds);
}

bool Ball::collidesWithEnemy(const PaddleEnemy& enemy, float dt) const {
    sf::Vector2f ballPos(xPos, yPos);
    sf::Vector2f nextBallPos(xPos + Speedx * dt, yPos + Speedy * dt);
    sf::FloatRect currentBallBounds(ballPos.x - radius, ballPos.y - radius, 2 * radius, 2 * radius);
    sf::FloatRect nextBallBounds(nextBallPos.x - radius, nextBallPos.y - radius, 2 * radius, 2 * radius);
    sf::FloatRect enemyBounds(1655.f, static_cast<float>(enemy.yPos), 20.f, 90.f);

    return nextBallBounds.intersects(enemyBounds);
}

void Ball::move(const PaddlePlayer& player, PlayerData& Data, EnemyData& EData, float dt, PaddleEnemy& enemy) {
    xPos += Speedx;
    yPos += Speedy;
    if (yPos > 610 || yPos < 0)
    {
        Speedy *= -1;
    }
    if (xPos > 1650) {
        std::cout << "Bot fail";
        Data.SetScore(1);
        Speedx *= -1;
    }
    if (xPos < 0)
    {
        std::cout << "Player fail";
        EData.SetScore(1);
        Speedx *= -1;
    }
    if (collidesWithPlayer(player, dt)) {
        std::cout << "Player hit!" << std::endl;
        xPos += 30;
        Speedx *= -1.01;
        //Data.SetScore(1);
    }
    if (collidesWithEnemy(enemy, dt))
    {
        xPos -= 30;
        Speedx *= -1.01;
    }
}

void Ball::ChangeSpeed(double XChange, double YChange) {
    Speedx += XChange;
    Speedy += YChange;
}