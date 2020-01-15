#include "dialog.h"
#include "ui_dialog.h"
#include "mapa.h"
#include "ship.h"
#include "player.h"
#include "bot.h"
#include <stdlib.h>
#include <QThread>
// Helper Functions //
list<Ship*>*  createShips(Map* map);
bool checkIsEnd(list<Ship*>* ship);


// GameProgressEvent //
GameProgressEvent::GameProgressEvent() : QEvent(QEvent::Type::User) {
    this->clickedPiece = nullptr;
}

GameProgressEvent::GameProgressEvent(Piece* clickedPiece) : QEvent(QEvent::Type::User) {
    this->clickedPiece = clickedPiece;
}

Piece* GameProgressEvent::getClickedPiece() {
    return this->clickedPiece;
}

// Dialog
Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    srand (static_cast<unsigned int>(time(nullptr)));

    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);


    playersMap = new Map(20,20,true);
    botsMap = new Map(340,20,true);

    for(int x = 0; x < 10; x++)
    {

        for(int y = 0; y < 10; y++)
        {
            scene->addItem(playersMap->getPiece(x,y));
            scene->addItem(botsMap->getPiece(x,y));
        }
    }


    this->playerShips = createShips(playersMap);
    this->botShips = createShips(botsMap);

     scene->addItem(playersMap);
     scene->addItem(botsMap);

    // maps and ships ready
    update();



    this->currentGamePhase = GamePhase::BOT_TURN;



    delete ui;
}

void Dialog::playTheGame(GameProgressEvent* event)
{

    if (currentGamePhase == GamePhase::PLAYER_TURN) {

        std::cout << "Player's move: ";
        Piece* clickedPiece = event->getClickedPiece();

        if (clickedPiece->getState() == State::SHIP) {
            clickedPiece->setState(State::HIT);
            std::cout << "hit"<<endl;
            if (checkIsEnd(botShips)) {
                std::cout << "END, PLAYER WON" << flush;
                // display prompt & exit application ?
            }
        } else {
            clickedPiece->setState(State::MISS);
            currentGamePhase = BOT_TURN;
            std::cout << "miss"<<endl;
        }


    } else {
        // Bot's Turn - TODO

        bool status;
        do
        {

         status = bot->takeTurn(playersMap);
         QThread::msleep(100);
         if (checkIsEnd(playerShips)) {
             std::cout << "END, BOT WON" << flush;
             // display prompt & exit application ?
         }
            playersMap->update();
        }while(status);
        currentGamePhase = BOT_TURN;
    }


    botsMap->update();

}

bool Dialog::event(QEvent *event) {

    if (event->type() == QEvent::Type::User) {
        playTheGame((GameProgressEvent*) event);
        return true;
    }

    return QDialog::event(event);
}

Dialog::~Dialog() {

}

list<Ship*>*  createShips(Map* map)
{
    list<Ship*>* listShip = new list<Ship*>();



    for(int i = 0; i < 2;i++){

        listShip->push_back(Ship::createThreeMast(map));
    }

    for(int i = 0; i < 3;i++){
        listShip->push_back(Ship::createTwoMast(map));


    }
    for(int i = 0; i < 4;i++){
        listShip->push_back(Ship::createOneMast(map));
    }
    return listShip;
}


bool checkIsEnd(list<Ship*>* ship)
{
    for(list<Ship*>::iterator it = ship->begin(); it != ship->end(); it++)
    {
        Ship* ship = (*it);
        if(!ship->isSunk())
        {
            return false;
        }

    }
    return true;
}
