#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "memtrace.h"
#include "Player.h"
#include "Snake.h"
#include "Field.h"
#include "Targy.h"

class Game {
private:
    Player* player;
    Field field;
    Snake snake;
    Obstacle* obstacles;
    class Apple apple;
    class GhostApple ghostApple;
    class SlowTime slowTime;
    int ms;
    int walls;
    Storm storm;

public:
    void generateWalls(int walls);
    Game(Player* p, int w, int h, int ms, int walls) : player(p), field(w, h), snake(w / 2, h / 2),ms(ms),walls(walls) {}
    Player* start();
    void printField();
    void generateApple();
    void generateSlowTime();
    void generateGhostApple();
    void generateStorm();
    ~Game(){delete[] obstacles;}
};
#endif // GAME_H_INCLUDED
