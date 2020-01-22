#ifndef GAMELOGIC_H
#define GAMELOGIC_H

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
class GameLogic;
}

class GameLogic : public QDialog
{
    Q_OBJECT

public:

    explicit GameLogic(QWidget *parent = nullptr);
    ~GameLogic() override;

    bool event(QEvent *event) override;

    void playTheGame(GameProgressEvent* event);

private:
    Ui::GameLogic *ui;
    QGraphicsScene *scene;

    Map* playersMap;
    Map* botsMap;
    QString liczbaStatkow;
    Bot* bot;


    list<Ship*>* playerShips;
    list<Ship*>* botShips;

    GamePhase currentGamePhase;

};




#endif // DIALOG_H
