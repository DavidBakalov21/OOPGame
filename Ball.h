#pragma once
class PaddlePlayer; 
class PaddleEnemy;
class PlayerData;
class EnemyData;
class Ball {
public:
    double xPos = 300;
    double yPos = 300;
    double Speedy = 3;
    double Speedx = 3;
    double radius = 15;

    bool collidesWithPlayer(const PaddlePlayer& player, float dt) const;
    bool collidesWithEnemy(const PaddleEnemy& enemy, float dt) const;

    void move(const PaddlePlayer& player, PlayerData& Data, EnemyData& EData, float dt, PaddleEnemy& enemy);
    void ChangeSpeed(double XChange, double YChange);
};