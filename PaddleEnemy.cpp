#include "PaddleEnemy.h"
#include "Ball.h"

void PaddleEnemy::moveUp() {
    if (yPos > 0) {
        yPos -= 3.3;
    }
}

void PaddleEnemy::moveDown() {
    if (yPos < 610) {
        yPos += 3.3;
    }
}

void PaddleEnemy::moveTowardsPredictedPosition(const Ball& ball) {
    double predictedY = ball.yPos + (ball.Speedy / ball.Speedx) * (xPos - ball.xPos);
    if (predictedY < yPos + size / 2) {
        moveDown();
    }
    else if (predictedY > yPos + size / 2) {
        moveUp();
    }
}