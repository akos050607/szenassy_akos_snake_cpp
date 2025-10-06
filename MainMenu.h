#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED
#include "memtrace.h"
#include "Player.h"

void resetCursorPosition();

class MainMenu {
private:
    Player* players;
    int numberOfPlayers;
public:
    void loadPlayers();
    MainMenu();
    void savePlayers(const Player* player);
    bool menu();
    ~MainMenu();
};
#endif // MAINMENU_H_INCLUDED
