#ifndef MAPA_H
#define MAPA_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QObject>
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
    BLANK = 3,   // ocean
    SUNK = 4    //zatopiony
};



enum GamePhase
{
    PREPARE = 0,
    BOT_TURN = 1,
    PLAYER_TURN = 2
};

class Piece :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Piece();
    Piece(const Piece &piece);
    Piece(int x, int y, int size,bool paintShipStatus);
    ~Piece() override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setState(State state);

    State getState();
    Ship* getShip();

    void setPointerShip(Ship* shipPointer);
    QRectF boundingRect() const override;
    bool shouldPaintShipStatus;
    void setMapPositionX(int mapX);
    void setMapPositionY(int mapY);
    int getMapPositionX();
    int getMapPositionY();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QRect qtRectangle;
    State state;
    Ship* shipPointer;
    int mapPositionX;
    int mapPositionY;

};




class Map : public QGraphicsItem
{
public:
    //Map(const Map &map);
    Map(int x0, int y0, bool shouldPaintShipStatus ,int size = 10, int pieceSize = 30 );
    ~Map() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    Piece* getPiece(int x, int y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;




private:

    std::vector<std::vector<Piece*>> pieces;
    int size;
    int x0;
    int y0;


};





#endif // MAPA_H

