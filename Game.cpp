#include "memtrace.h"
#include <iostream>
#include "Game.h"
#include "Player.h"
#ifndef CPORTA
#include <conio.h>
#include <windows.h>
#endif
using namespace std;
#ifndef CPORTA
char getLatestKey() {
    char last = 0;
    while (_kbhit()) {
        last = _getch();
    }
    return last;
}
void resetCursorPosition() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

int getRandom(int max) {
    return rand() % (max + 1);
}

Player* Game::start()
{
    srand(time(0));
    player->updateScore();
    generateApple();
    generateGhostApple();
    generateSlowTime();
    generateWalls(walls);
    generateStorm();
    bool over = false;
    char c;
    int dx=0;int dy=1;
    system("cls");
    while(!over)
    {
        #ifndef CPORTA
        resetCursorPosition();
        #endif
        snake.move(dx,dy);
        if(snake[0].first==-1||snake[0].first==field.getWidth()||snake[0].second==-1||snake[0].second==field.getHeight())
        {
            over=true;
        }
        for(int i=1;i<snake.getSize();i++)
        {
            if(snake.getGhost()==0 && (snake[0]==snake[i]))
            {
                over=true;
            }
        }
        for(int i=0;i<walls;i++)
        {
            if(snake.getGhost()==0 && (snake[0]==obstacles[i].getPosition()))
            {
                over=true;
            }
        }
        if(storm.getInd()<7 && ((storm.getPosition().first <= snake[0].first+1 && storm.getPosition().first >= snake[0].first-1) || (storm.getPosition().second <= snake[0].second+1 && storm.getPosition().second >= snake[0].second-1)))
        {
            over=true;
        }
        if(storm.getInd()==0) generateStorm();
        if(snake[0]==apple.getPosition()){
            apple.eatenBy(&snake);
            generateApple();
            if(walls==0)
            {
                player->updateScore(1000/ms);
            }
            else player->updateScore((walls/5)*(1000/ms));
        }
        if(snake[0]==ghostApple.getPosition()){
            ghostApple.eatenBy(&snake);
            ghostApple.setPosition(-1,-1);
        }
        if(snake.getGhost()==1) generateGhostApple();
        if(snake[0]==slowTime.getPosition()){
            slowTime.eatenBy(&snake);
            slowTime.setPosition(-1,-1);
        }
        if(snake.getT()==1) generateSlowTime();
        printField();
        snake.decT();
        snake.decG();
        storm.decI();
        #ifndef CPORTA
        if(snake.getT()>0) Sleep(ms*2);
        else Sleep(ms);
        #endif
        #ifndef CPORTA
        c=getLatestKey();
        #endif
        #ifdef CPORTA
        c=getchar();
        #endif // CPORTA
        switch(c)
        {
            case 'w':
                if(dy!=-1)
                {
                    dy=1;
                    dx=0;
                }
                break;
            case 'a':
                if(dx!=1)
                {
                    dy=0;
                    dx=-1;
                }
                break;
            case 's':
                if(dy!=1)
                {
                    dy=-1;
                    dx=0;
                }
                break;
            case 'd':
                if(dx!=-1)
                {
                    dy=0;
                    dx=1;
                }
                break;
            case 27:
                over=true;
                break;
        }
    }
    return player;
}

void Game::printField()
{
    int h = field.getHeight();
    int w = field.getWidth();
    bool semmi;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            semmi=true;
            for(int i=0;i<snake.getSize();i++)
            {
                if (snake[i].first == x && snake[i].second == y) {
                    if (i == 0)
                        cout << "X ";
                    else
                        cout << "O ";
                    semmi = false;
                    break;
                }
            }
            if(storm.getInd()<=12 && storm.getInd()>=7 && storm.getPosition()==pair<int,int>{x,y} && semmi)
            {
                cout<<"@ ";
                semmi=false;
            }
            if(semmi && storm.getInd()<7 && ((storm.getPosition().first <= x+1 && storm.getPosition().first >= x-1) || (storm.getPosition().second <= y+1 && storm.getPosition().second >= y-1)))
            {
                cout<<"@ ";
                semmi=false;
            }
            if(apple.getPosition()==pair<int,int>{x,y} && semmi)
            {
                cout<< "A ";
                semmi=false;
            }
            if(slowTime.getPosition()==pair<int,int>{x,y} && semmi)
            {
                cout<< "T ";
                semmi=false;
            }
            if(ghostApple.getPosition()==pair<int,int>{x,y} && semmi)
            {
                cout<< "G ";
                semmi=false;
            }
            for(int i=0;i<walls;i++)
            {
                if (obstacles[i].getPosition() == pair<int,int>{x,y} && semmi) {
                    cout<<"# ";
                    semmi = false;
                    break;
                }
            }
            if(semmi) cout<<". ";
        }
        cout << endl;
    }
    cout<< player->getCurrentScore() << "             " << player->getBestScore();
    cout << endl;
}

void Game::generateApple()
{
    bool notPlaceAble;
    int x,y;
    do
    {
        x=getRandom(field.getWidth()-1);
        y=getRandom(field.getHeight()-1);
        notPlaceAble = true;
        for(int i=0;i<snake.getSize();i++)
        {
            if (snake[i] == pair<int,int>{x,y}) notPlaceAble = false;
        }
    } while(!notPlaceAble);
    apple.setPosition(x,y);
}

void Game::generateGhostApple()
{
    bool notPlaceAble;
    int x,y;
    do
    {
        x=getRandom(field.getWidth()-1);
        y=getRandom(field.getHeight()-1);
        notPlaceAble = true;
        for(int i=0;i<snake.getSize();i++)
        {
            if (snake[i] == pair<int,int>{x,y}) notPlaceAble = false;
        }
    } while(!notPlaceAble);
    ghostApple.setPosition(x,y);
}

void Game::generateSlowTime()
{
    bool notPlaceAble;
    int x,y;
    do
    {
        x=getRandom(field.getWidth()-1);
        y=getRandom(field.getHeight()-1);
        notPlaceAble = true;
        for(int i=0;i<snake.getSize();i++)
        {
            if (snake[i] == pair<int,int>{x,y}) notPlaceAble = false;
        }
    } while(!notPlaceAble);
    slowTime.setPosition(x,y);
}

void Game::generateWalls(int walls)
{
    obstacles = new Obstacle[walls];
    for(int i=0;i<walls;i++)
    {
        int x,y;
        do
        {
            x=getRandom(field.getWidth()-1);
            y=getRandom(field.getHeight()-1);

        } while(snake[0] == pair<int,int>{x,y} || apple.getPosition() == pair<int,int>{x,y} || slowTime.getPosition() == pair<int,int>{x,y} || ghostApple.getPosition() == pair<int,int>{x,y});
        obstacles[i].setPosition(x,y);
    }
}

void Game::generateStorm()
{
    bool notPlaceAble;
    int x,y;
    do
    {
        x=getRandom(field.getWidth()-1);
        y=getRandom(field.getHeight()-1);
        notPlaceAble = true;
        for(int i=0;i<snake.getSize();i++)
        {
            if (snake[i] == pair<int,int>{x,y}) notPlaceAble = false;
        }
    } while(!notPlaceAble);
    storm.setPosition(x,y);
    storm.setInd(20);
}
