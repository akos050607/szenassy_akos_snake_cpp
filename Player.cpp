#include "memtrace.h"
#include "Player.h"


Player::Player(const String& playerName) : name(playerName), currentScore(0), bestScore(0){}

void Player::updateScore() {
    currentScore = 0;
}



void Player::updateScore(int score) {
    currentScore+=score;
    if (currentScore > bestScore) bestScore = currentScore;
}

void Player::setBestScore(int score) {bestScore = score;}
String Player::getName() const { return name; }

int Player::getCurrentScore() const { return currentScore; }
int Player::getBestScore() const { return bestScore; }
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        currentScore = other.currentScore;
        bestScore = other.bestScore;
    }
    return *this;
}

