#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#include "memtrace.h"
class Field {
private:
    int width;
    int height;

public:
    Field(int w, int h) : width(w), height(h) {}
    int getHeight(){return height;}
    int getWidth(){return width;}
};

#endif // FIELD_H_INCLUDED
