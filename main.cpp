#include "memtrace.h"
#include <iostream>
#include "MainMenu.h"
#include "Player.h"
#include "Snake.h"
#include "Field.h"
#include "Game.h"
#include "Targy.h"
#include <cassert>
using namespace std;
#ifndef CPORTA
int main() {
    MainMenu menu;
    while(menu.menu()){}
    return 0;
}
#endif // CPORTA
#ifdef CPORTA

void clearTestFile() {
    std::ofstream out("scores.txt", std::ios::trunc);
    out.close();
}

void testPlayer() {
    clearTestFile();

    Player p1("TestPlayer");
    assert(p1.getName() == "TestPlayer");
    assert(p1.getCurrentScore() == 0);
    assert(p1.getBestScore() == 0);

    p1.updateScore(100);
    assert(p1.getCurrentScore() == 100);
    assert(p1.getBestScore() == 100);

    p1.updateScore(50);
    assert(p1.getCurrentScore() == 150);
    assert(p1.getBestScore() == 150);

    p1.updateScore();
    assert(p1.getCurrentScore() == 0);
    assert(p1.getBestScore() == 150);

    p1.setBestScore(200);
    assert(p1.getBestScore() == 200);

    Player p2 = p1;
    assert(p2.getName() == "TestPlayer");
    assert(p2.getBestScore() == 200);

    std::cout << "Player class tests passed!\n";
}

// Test cases for Snake class
void testSnake() {
    Snake snake(10, 10);

    snake.grow();
    snake.grow();
    assert(snake.getSize() == 3);

    snake[0] = {10, 10};
    snake[1] = {10, 11};
    snake[2] = {10, 12};

    snake.move(1, 0);
    assert(snake[0].first == 11 && snake[0].second == 10);
    assert(snake[1].first == 10 && snake[1].second == 10);
    assert(snake[2].first == 10 && snake[2].second == 11);

    snake.move(0, 1);
    assert(snake[0].first == 11 && snake[0].second == 9);
    assert(snake[1].first == 11 && snake[1].second == 10);
    assert(snake[2].first == 10 && snake[2].second == 10);

    snake.move(-1, 0);
    assert(snake[0].first == 10 && snake[0].second == 9);
    assert(snake[1].first == 11 && snake[1].second == 9);
    assert(snake[2].first == 11 && snake[2].second == 10);

    snake.move(0, -1);
    assert(snake[0].first == 10 && snake[0].second == 10);
    assert(snake[1].first == 10 && snake[1].second == 9);
    assert(snake[2].first == 11 && snake[2].second == 9);

    snake.grow();
    assert(snake.getSize() == 4);
    snake.move(1, 0);
    assert(snake[3].first == 11 && snake[3].second == 9);

    assert(snake.getGhost() == 0);
    snake.setGhost(5);
    assert(snake.getGhost() == 5);
    snake.decG();
    assert(snake.getGhost() == 4);

    assert(snake.getT() == 0);
    snake.setT(3);
    assert(snake.getT() == 3);
    snake.decT();
    assert(snake.getT() == 2);

    snake[0] = {15, 15};
    snake[1] = {15, 16};
    snake[2] = {15, 17};

    assert(snake[0].first == 15 && snake[0].second == 15);
    assert(snake[1].first == 15 && snake[1].second == 16);
    assert(snake[2].first == 15 && snake[2].second == 17);

    pair<int, int>& headRef = snake[0];
    headRef.first = 20;
    headRef.second = 20;
    assert(snake[0].first == 20 && snake[0].second == 20);

    std::cout << "Snake tesztelve\n";
}

void testTargy() {
    Snake snake(5, 5);

    Apple apple;
    apple.setPosition(5, 5);
    assert(apple.getPosition().first == 5);
    assert(apple.getPosition().second == 5);

    int eredeti = snake.getSize();
    apple.eatenBy(&snake);
    assert(snake.getSize() == eredeti + 1);

    GhostApple gApple;
    gApple.setPosition(5, 5);
    assert(gApple.getPosition().first == 5);
    assert(gApple.getPosition().second == 5);

    assert(snake.getGhost() == 0);
    gApple.eatenBy(&snake);
    assert(snake.getGhost() == 10);

    SlowTime sTime;
    sTime.setPosition(5, 5);
    assert(sTime.getPosition().first == 5);
    assert(sTime.getPosition().second == 5);

    assert(snake.getT() == 0);
    sTime.eatenBy(&snake);
    assert(snake.getT() == 8);

    cout << "Targy tesztelve!\n";
}


int main() {
    testPlayer();
    testSnake();
    testTargy();
    cout << "Minden mukodik!\n";
    return 0;
}
#endif
