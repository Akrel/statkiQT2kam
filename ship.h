#ifndef SHIP_H
#define SHIP_H

#include "mapa.h"

using namespace std;
class Piece;
class Map;
class Ship
{
public:

    Ship(list<Piece *> *listOfpiece );
    ~Ship();

    bool isSunk();
    static bool checkIfCanBeShip(Map *map, int x, int y);

    static Ship* createTwoMast(Map* Obiekt);
    static Ship* createOneMast(Map* Obiekt);
    static Ship* createThreeMast(Map* Obiekt);
    bool isBlank(Piece* piece);
    list<Piece *>* getListShip();
    void setIsSunk();
    void setNeighborsMiss(Map *map);
private:
    list<Piece*>* pieces;
    static list<Piece*>* createTwoMastVertical(Map *Obiekt, int x, int y);
    static list<Piece*>*  createThreeMastVertical(Map* Obiekt, int x, int y) ;
    static list<Piece*>*  createThreeMastHorizontal(Map *Obiekt, int x, int y);
    static list<Piece*>* createTwoMastHorizontal(Map *Obiekt, int x, int y);


};

#endif // SHIP_H
