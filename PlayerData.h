#pragma once
#include <string>
class PlayerData {
public:
    std::string PlayerName;
    int Score = 0;
    void SetScore(int score);
};