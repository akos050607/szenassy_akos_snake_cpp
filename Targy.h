#ifndef TARGY_H_INCLUDED
#define TARGY_H_INCLUDED
#include "memtrace.h"
#include <iostream>
#include "Snake.h"

class Fruit {
protected:
    pair<int, int> position;
public:
    Fruit(int x, int y) {
        position.first = x;
        position.second = y;
    }
    pair<int, int> getPosition() const { return position; }
    void setPosition(int x,int y) {
        position.first = x;
        position.second = y;
    }
    virtual void eatenBy(Snake* s) = 0;
    virtual ~Fruit() {}
};

class Apple: public Fruit {
public:
    Apple() : Fruit(0, 0) {}
    void eatenBy(Snake* s);
};

class SlowTime: public Fruit{
public:
    SlowTime(): Fruit(0,0){}
    void eatenBy(Snake* s);
};

class GhostApple: public Fruit{
public:
    GhostApple(): Fruit(0,0){}
    void eatenBy(Snake* s);
};

class Storm{
    pair<int,int> position;
    int indicator;
public:
    Storm() :position({-1,-1}),indicator(15){}
    pair<int,int> getPosition(){return position;}
    void setPosition(int x,int y){position = {x,y};}
    int getInd(){return indicator;};
    void setInd(int i){indicator=i;};
    void decI(){if(indicator!=0) indicator--;}
};

class Obstacle{
    pair<int,int> position;
public:
    Obstacle() :position({0,0}){}
    Obstacle(int x, int y) :position({x,y}){}
    pair<int,int> getPosition(){return position;}
    void setPosition(int x,int y){position = {x,y};}
};

#endif // TARGY_H_INCLUDED
