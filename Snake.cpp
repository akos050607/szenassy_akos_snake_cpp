#include "memtrace.h"
#include <iostream>
#include "Snake.h"

void Snake::resize() {
    pair<int, int>* newBody = new pair<int, int>[bodySize+1];
    for (int i = 0; i < bodySize; i++) {
        newBody[i] = body[i];
    }
    delete[] body;
    body = newBody;
}

Snake::Snake(int startX, int startY):bodySize(1),ghost(0),slowTime(0){
    body = new pair<int,int>[1];
    body[0].first = startX;
    body[0].second = startY;
}

pair<int,int>& Snake::operator[](int i)
{
    return body[i];
}


void Snake::move(int dx, int dy) {
    tail = body[bodySize-1];
    for (int i = bodySize-1; i !=0; i--) {
        body[i].first = body[i-1].first;
        body[i].second = body[i-1].second;
    }
    body[0].first += dx;
    body[0].second -= dy;
}

void Snake::grow() {
    resize();
    body[bodySize]=tail;
    bodySize++;
}
