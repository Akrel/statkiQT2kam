#ifndef MAPA_H
#define MAPA_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <vector>
#include <qgraphicsitem.h>
#include <stdio.h>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
class Ship;
#include "ship.h"
enum State
{
    SHIP = 0,   // statek plywa
    HIT = 1,    // statek trafiony
    MISS = 2,   // pudlo
    BLANK = 3   // ocean
};



enum GamePhase
{
    PREPARE = 0,
    GAME = 1
};

class Piece : public QGraphicsItem
{
public:
    Piece(const Piece &piece);
    Piece(int x, int y, int size,bool paintShipStatus);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setState(State state);

    State getState();
    Ship* getShip();

    void setPointerShip(Ship* shipPointer);
    QRectF boundingRect() const override;
    bool shouldPaintShipStatus;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QRect qtRectangle;
    State state;
    Ship* shipPointer;

};




class Map : public QGraphicsItem
{
public:
    //Map(const Map &map);
    Map(int x0, int y0, bool shouldPaintShipStatus ,int size = 10, int pieceSize = 30 );
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    Piece* getPiece(int row, int col);

    void returnsomething(Piece*);




private:

    std::vector<std::vector<Piece*>> pieces;
    int size;


};





#endif // MAPA_H

