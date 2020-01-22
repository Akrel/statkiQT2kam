
#include "QCoreApplication"
#include "mapa.h"
#include "mainwindow.h"
extern Dialog* oknodwa;
using namespace std;

Qt::GlobalColor getColor(State state) {

    switch (state)
    {
    case SHIP:
        return Qt::black;
    case HIT:
        return  Qt::red;
    case MISS:
        return Qt::gray;
    case BLANK:
        return Qt::white;
    case SUNK:
        return Qt::darkRed;
    }
}


// size - wymiar mapy, ilosc kratek wysokosci / szerokosci
// x0, y0 - wspolrzedne lewego gornego rogu
//
Map::Map(int x0, int y0,  bool shouldPaintShipStatus, int size, int pieceSize)
{
    this->size = size;
    this->x0 = x0;
    this->y0 = y0;

    int y = y0;
    for (int i = 0; i < size; i++) {

        vector<Piece*> *row = new vector<Piece*>();

        int x = x0;
        for (int j = 0; j < size; j++) {
            cout << "x " << x <<", y " << y << endl;//"x " <<"x " <<
            Piece *piece = new Piece(x, y, pieceSize,shouldPaintShipStatus);
            piece->setMapPositionY(i);
            piece->setMapPositionX(j);
            row->push_back(piece);
            x = x + pieceSize;
        }
        this->pieces.push_back(*row);
        y = y + pieceSize;
    }

}



QRectF Map::boundingRect() const
{
    return QRectF(x0, y0, 30*size, 30*size); // TODO- hardkodowane 30, fix
}



void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(std::vector<int>::size_type row = 0; row != pieces.size(); row++) {
        for(std::vector<int>::size_type col = 0; col != pieces[row].size(); col++) {
            pieces[row][col]->paint(painter, option, widget);
        }
    }

}


Piece *Map::getPiece(int x, int y){


    cout <<"row: " << x << " col: " << y << flush << endl;
    if(x > 9 || x < 0 || y > 9 || y < 0 )
    {
        return nullptr;

    }
    else
    {
        Piece* piece = pieces[y][x];
        cout <<"piece X: " <<piece->getMapPositionX()<<" Y: "<< piece->getMapPositionY() << flush << endl;
        return piece;
    }

}

void Map::setEvetsActive(bool boolEventAvtive)
{
    this->eventsAvtive = boolEventAvtive;
}


void Map::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(this->eventsAvtive == true){
        update();
        QGraphicsItem::mousePressEvent(event);
    }

}


Piece::Piece(const Piece &piece)
{
    qtRectangle = piece.qtRectangle;
    state = piece.state;
}


Piece::Piece(int x, int y, int size,bool paintsShipStatus) {
    cout << "Creating Piece..." << endl;
    qtRectangle = QRect(x, y, size, size);
    state = State::BLANK;
    shouldPaintShipStatus = paintsShipStatus;
}

QRectF Piece::boundingRect() const
{
    return QRectF(qtRectangle.x(), qtRectangle.y(), qtRectangle.width(), qtRectangle.height());
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && (state == SHIP || state == BLANK)) {

        QCoreApplication::sendEvent(oknodwa, new GameProgressEvent(this));
        update();
    }
}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (state == SHIP)
    {
        if(shouldPaintShipStatus)
        {
            //cout << "Painting Piece..." << endl;
            Qt::GlobalColor color = getColor(state);
            QBrush brush(color);

            painter->fillRect(qtRectangle, brush);
            painter->drawRect(qtRectangle);
        }
        else {
            Qt::GlobalColor color = getColor(BLANK);
            QBrush brush(color);

            painter->fillRect(qtRectangle, brush);
            painter->drawRect(qtRectangle);
        }
    }
    else
    {
        //cout << "Painting Piece..." << endl;
        Qt::GlobalColor color = getColor(state);
        QBrush brush(color);

        painter->fillRect(qtRectangle, brush);
        painter->drawRect(qtRectangle);
    }
}

void Piece::setState(State state)
{
    this->state = state;
}


State Piece::getState()
{
    return state;
}



Ship* Piece::getShip()
{
    return shipPointer;
}

void Piece::setPointerShip(Ship* pointerShip)
{
    this->shipPointer = pointerShip;
}

void Piece::setMapPositionX(int mapX)
{
    this->mapPositionX = mapX;
}

int Piece::getMapPositionX()
{
    return mapPositionX;
}

void Piece::setMapPositionY(int mapY)
{
    this->mapPositionY = mapY;
}
int Piece::getMapPositionY()
{
    return mapPositionY;
}

Map :: ~Map()
{
    for(std::vector<int>::size_type row = 0; row != pieces.size(); row++) {
        for(std::vector<int>::size_type col = 0; col != pieces[row].size(); col++) {
            delete pieces[row][col];
        }
    }

}

Piece :: ~Piece()
{
    delete shipPointer;
}
