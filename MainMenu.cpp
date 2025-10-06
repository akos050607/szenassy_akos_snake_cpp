#include "memtrace.h"
#include "MainMenu.h"
#include <iostream>
#include <fstream>
#ifndef CPORTA
#include <conio.h>
#include <windows.h>
#endif
#include "string5.h"
#include "Player.h"
#include "Game.h"
using namespace std;

void MainMenu::loadPlayers()
{
    ifstream in("scores.txt");
    String name;
    int best;
    while (in >> name >> best) {
        Player* tempPlayers = new Player[numberOfPlayers+1];
        for (int i = 0; i < numberOfPlayers; i++) {
            tempPlayers[i] = players[i];
        }
        Player tempPlayer(name);
        tempPlayer.setBestScore(best);
        tempPlayers[numberOfPlayers] = tempPlayer;
        delete[] players;
        players = tempPlayers;
        numberOfPlayers++;
    }
    in.close();
}

MainMenu::MainMenu()
{
    numberOfPlayers = 0;
    players = new Player[0];
    loadPlayers();
}

void MainMenu::savePlayers(const Player* player) {
    ofstream out("scores.txt");
    if (!out.is_open()) {
        cout << "Nem sikerült megnyitni a fájlt!" << endl;
        return;
    }

    for (int i = 0; i < numberOfPlayers; ++i) {
        if(players[i].getName() == player->getName()) out << player->getName() << " " << player->getBestScore() << endl;
        else out << players[i].getName() << " " << players[i].getBestScore() << endl;
    }
    out.close();
}

bool MainMenu::menu()
{
    system("cls");
    char c;
    String options[] = {"jatek inditasa","palyameret" ,"nehezseg", "bezaras"};
    int cursor=0;
    int w=20,h=20;
    int ms =200;
    int walls = 0;
    bool start = false;
    bool close = false;
    String name;
    cout << "Enter your name: ";
    cin >> name;
    int j=0;
    Player* currentPlayer;
    while(j<numberOfPlayers)
    {
        if(players[j].getName() == name)
        {
            currentPlayer = &players[j];
            break;
        }
        j++;
    }
    if(j==numberOfPlayers)
    {
        Player* tempPlayers = new Player[numberOfPlayers+1];
        for (int i = 0; i < numberOfPlayers; i++) {
            tempPlayers[i] = players[i];
        }
        Player tempPlayer(name);
        tempPlayers[numberOfPlayers] = tempPlayer;
        delete[] players;
        players = tempPlayers;
        numberOfPlayers++;
        currentPlayer = &players[j];
    }
    savePlayers(currentPlayer);
    system("cls");

    while(!start && !close)
    {
        #ifndef CPORTA
        resetCursorPosition();
        #endif
        for(int i=0;i<4;i++)
        {
            if(i==cursor) cout<<options[i].capital()<<endl;
            else cout<<options[i]<<endl;
        }
        #ifndef CPORTA
        c=_getch();
        if(cursor!=0 && c=='w') cursor-=1;
        if(cursor!=3 && c=='s') cursor+=1;
        Sleep(20);
        #endif // CPORTA
        #ifdef CPORTA
        c=getchar();
        #endif // CPORTA
        if(c=='\t')
        {
            switch(cursor)
            {
                case 0: start=true;break;
                case 1:
                    system("cls");
                    cout << "magassag?(20-40): ";
                    cin >> h;
                    cout << "selesseg?(20-40): ";
                    cin >> w;
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    cout << "sebesség(ms): ";
                    cin >> ms;
                    cout << "fal db: ";
                    cin >> walls;
                    system("cls");
                    break;
                case 3:
                    close=true;
                    break;
            }
        }
    }
    if(close) return false;
    Game game(currentPlayer,w,h,ms,walls);
    savePlayers(game.start());
    return true;
}
MainMenu::~MainMenu(){delete[] players;}
