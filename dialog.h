#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "mapa.h"
#include "ship.h"
#include "bot.h"
#include "player.h"


using namespace std;

class GameProgressEvent : public QEvent {

private:
    Piece* clickedPiece;
public:
    GameProgressEvent();
    GameProgressEvent(Piece*);
    Piece* getClickedPiece();

};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

    bool event(QEvent *event) override;

    void playTheGame(GameProgressEvent* event);

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;

    Map* playersMap;
    Map* botsMap;

    Bot* bot;
    Player* humanPlayer;

    list<Ship*>* playerShips;
    list<Ship*>* botShips;

    GamePhase currentGamePhase;

};




#endif // DIALOG_H
