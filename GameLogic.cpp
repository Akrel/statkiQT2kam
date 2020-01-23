#include "GameLogic.h"

extern GameLogic* oknodwa;
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
GameLogic::GameLogic(QWidget *parent) : QDialog(parent), ui(new Ui::GameLogic)
{
    srand (static_cast<unsigned int>(time(nullptr)));

    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
   // ui->label->setText("Liczba statkow: "+QString::number(51));
    playersMap = new Map(20,20,true);
    botsMap = new Map(340,20,true);

    playersMap->setEvetsActive(false);
    //botsMap->setEvetsActive(true);
    for(int x = 0; x < 10; x++)
    {

        for(int y = 0; y < 10; y++)
        {
            scene->addItem(playersMap->getPiece(x,y));
            scene->addItem(botsMap->getPiece(x,y));
        }
    }

    this->bot = new Bot();
    this->playerShips = createShips(playersMap);
    this->botShips = createShips(botsMap);
    scene->addItem(playersMap);
    scene->addItem(botsMap);

    // maps and ships ready
    update();



    this->currentGamePhase = GamePhase::PLAYER_TURN;



    delete ui;
}

void GameLogic::playTheGame(GameProgressEvent* event)
{

    if (currentGamePhase == GamePhase::PLAYER_TURN) {


        std::cout << "Player's move: ";
        Piece* clickedPiece = event->getClickedPiece();

        if (clickedPiece->getState() == State::SHIP) {
            clickedPiece->setState(State::HIT);
            std::cout << "hit"<<endl;
            if(clickedPiece->getShip()->isSunk())
            {

                clickedPiece->getShip()->setIsSunk();
                clickedPiece->getShip()->setNeighborsMiss(botsMap);
            }
            if (checkIsEnd(botShips)) {

                 //QMessageBox::information(this,"UPS","KONIEC GRY!");
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
            QCoreApplication::sendEvent(oknodwa, new GameProgressEvent());
            if (checkIsEnd(playerShips)) {
                std::cout << "END, BOT WON" << flush;
                // display prompt & exit application ?
                playersMap->update();
            }
            //  this->liczbaStatkow.append(QString::number(playerShips->size())); chciałem dodać statystyki ale chwilowo nie wiem jak
            QThread::msleep(150);

            playersMap->update();
        }while(status);
        currentGamePhase = PLAYER_TURN;
    }


    botsMap->update();

}

bool GameLogic::event(QEvent *event) {

    if (event->type() == QEvent::Type::User) {
        playTheGame((GameProgressEvent*) event);
        return true;
    }

    return QDialog::event(event);
}

GameLogic::~GameLogic() {
    delete playersMap;
    delete botsMap;
    delete botShips;
    delete  playerShips;
    delete scene;

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
