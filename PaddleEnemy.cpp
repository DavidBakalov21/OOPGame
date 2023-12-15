#include "PaddleEnemy.h"
#include "Ball.h"

void PaddleEnemy::moveUp() {
    if (yPos > 0) {
        yPos -= 1.9;
    }
}

void PaddleEnemy::moveDown() {
    if (yPos < 610) {
        yPos += 1.9;
    }
}

void PaddleEnemy::moveTowardsPredictedPosition(const Ball& ball) {
    double predictedY = ball.yPos + (ball.Speedy / ball.Speedx) * (xPos - ball.xPos);
    if (predictedY > yPos + size / 2) {
        moveDown();
    }
    else if (predictedY < yPos + size / 2) {
        moveUp();
    }
}