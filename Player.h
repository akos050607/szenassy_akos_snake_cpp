#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "memtrace.h"
#include "string5.h"

class Player {
private:
    String name;
    int currentScore = 0;
    int bestScore = 0;

public:
    Player() : name("Unknown") {}
    Player(const String& playerName);

    void updateScore(int score);
    void updateScore();
    void setBestScore(int score);
    String getName() const;

    int getCurrentScore() const;
    int getBestScore() const;
    Player& operator=(const Player& other);
};

#endif // PLAYER_H_INCLUDED
