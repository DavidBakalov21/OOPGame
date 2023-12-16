#include "PaddleEnemy.h"
#include "Ball.h"

void PaddleEnemy::moveUp() {
    if (yPos > 0) {
        yPos -= 12.3;
    }
}

void PaddleEnemy::moveDown() {
    if (yPos < 610) {
        yPos += 12.3;
    }
}

void PaddleEnemy::moveTowardsPredictedPosition(const Ball& ball) {
    if (ball.yPos > yPos ) {
        moveDown();
    }
    else if (ball.yPos < yPos ) {
        moveUp();
    }
}