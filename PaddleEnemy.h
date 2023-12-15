#pragma once
#include "Paddle.h"
class Ball;
class PaddleEnemy : public Paddle {
public:
    void moveUp();
    void moveDown();
    void moveTowardsPredictedPosition(const Ball& ball);
};
