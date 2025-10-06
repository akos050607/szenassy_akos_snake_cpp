#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "memtrace.h"
#include <iostream>

using namespace std;
class Snake {
private:
    pair<int, int>* body;
    int bodySize;
    void resize();
    pair<int,int> tail;
    int ghost;
    int slowTime;
public:
    Snake(int startX, int startY);

    int getSize(){return bodySize;}

    void move(int dx, int dy);

    void grow();

    pair<int,int>& operator[](int i);

    int getGhost(){return ghost;}

    void setGhost(int g){ghost = g;}

    int getT(){return slowTime;}

    void setT(int T){slowTime = T;}

    void decG()
    {
        if(ghost>0) ghost--;
    }
    void decT()
    {
        if(slowTime>0) slowTime--;
    }

    ~Snake(){delete[] body;}
};



#endif // SNAKE_H_INCLUDED
