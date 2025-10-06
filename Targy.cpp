#include "memtrace.h"
#include "Targy.h"


void Apple::eatenBy(Snake* s) {
    s->grow();
}

void GhostApple::eatenBy(Snake* s) {
    s->setGhost(10);
}

void SlowTime::eatenBy(Snake* s) {
    s->setT(8);
}
