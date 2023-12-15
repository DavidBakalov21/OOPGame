#include "PaddlePlayer.h"

void PaddlePlayer::moveUp() {
    if (yPos > 0) {
        yPos -= 1.9;
    }
}

void PaddlePlayer::moveDown() {
    if (yPos < 610) {
        yPos += 1.9;
    }
}