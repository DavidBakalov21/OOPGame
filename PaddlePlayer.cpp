#include "PaddlePlayer.h"

void PaddlePlayer::moveUp() {
    if (yPos > 0) {
        yPos -= 12;
    }
}

void PaddlePlayer::moveDown() {
    if (yPos < 610) {
        yPos += 12;
    }
}