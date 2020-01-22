#ifndef BOT_H
#define BOT_H
#include "mapa.h"
#include "ship.h"
#include "CoordinatsToShoot.h"
class Bot
{
public:
    Bot();
    bool takeTurn(Map* mapPlayer);
    ~Bot();
private:
    list<CoordinatsToShoot*>* position = new list<CoordinatsToShoot*>();

    int hitX = -1;
    int hitY = -1;



};

#endif // BOT_H
