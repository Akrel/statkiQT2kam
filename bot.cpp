#include "bot.h"
#include <QThread>
Bot::Bot()
{
    //list<CoordinatsToShoot*>* neposition = new list<CoordinatsToShoot*>();
    this->position =  new list<CoordinatsToShoot*>();

}


bool Bot :: takeTurn(Map* mapPlayer)
{


    if(this->position->empty()) // jesli lista pozycja pusta losujemy z randa
    {
        int x,y;

        do
        {
            x = qrand() % 10;
            y = qrand() % 10;

        }while (mapPlayer->getPiece(x,y)->getState() != State::SHIP && mapPlayer->getPiece(x,y)->getState() != State::BLANK);

        if(mapPlayer->getPiece(x,y)->getState() == State::SHIP) //strzal
        {
            mapPlayer->getPiece(x,y)->setState(HIT);
            if(mapPlayer->getPiece(x,y)->getShip()->isSunk() == true)
            {
                mapPlayer->getPiece(x,y)->getShip()->setIsSunk();
                mapPlayer->getPiece(x,y)->getShip()->setNeighborsMiss(mapPlayer);

            }
            else
            {
                this->hitX = x;
                this->hitY = y;
                position->push_back(oneDownPoint);
                position->push_back(oneUpPoint);
                position->push_back(oneLeftPoint);
                position->push_back(oneRightPoint);

            }
            return true;
        }
        else {
            mapPlayer->getPiece(x,y)->setState(State::MISS);
            return false;
        }

    }
    else
    {
        int x = 0 ,y = 0;
        CoordinatsToShoot* cordToShot;

        do{

            if(position->empty())
            {
                break;
            }
            cordToShot = position->front();

            cout <<"aktualny strzal: " <<cordToShot->getShiftX() <<" " << cordToShot->getShiftY() << endl;

            position->pop_front();

            x = this->hitX + cordToShot->getShiftX();
            y = this->hitY + cordToShot->getShiftY();


        }  while(mapPlayer->getPiece(x,y) == nullptr || (mapPlayer->getPiece(x,y)->getState() != SHIP && mapPlayer->getPiece(x,y)->getState() != BLANK));

        if(position->empty())
        {
            cout<< "WARNING - POSITION EMPTY" << endl <<flush;
        }

        if(mapPlayer->getPiece(x,y)->getState() == State::SHIP)
        {
            cout<< "\ntrafilem statek"<< endl <<flush;
            mapPlayer->getPiece(x,y)->setState(State::HIT);
            if(mapPlayer->getPiece(x,y)->getShip()->isSunk() == true)
            {
                mapPlayer->getPiece(x,y)->getShip()->setIsSunk();
                position->clear();
                mapPlayer->getPiece(x,y)->getShip()->setNeighborsMiss(mapPlayer);

            }

            else
            {
                this->hitX = x;
                this->hitY = y;

                if(cordToShot == oneLeftPoint)
                {
                    cout << "HIT ONE LEFT"<< endl;
                    cout << "POSITION SIZE: " << position->size() << endl;
                    position->clear();  // XXXXXXX
                    position->push_back(oneLeftPoint);
                    position->push_back(twoRightPoint);
                    cout << "POSITION[0] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                    cout << "POSITION[1] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                }
                else if(cordToShot == oneRightPoint )
                {
                    cout << "HIT ONE RIGHT"<< endl;
                    cout << "POSITION SIZE: " << position->size() << endl;
                    position->clear();// XXXXXXX
                    position->push_back(oneRightPoint);
                    position->push_back(twoLeftPoint);
                    cout << "POSITION[0] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                    cout << "POSITION[1] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;

                }
                else if(cordToShot == oneDownPoint)
                {
                    cout << "HIT ONE DOWN"<< endl;
                    cout << "POSITION SIZE: " << position->size() << endl;
                    position->clear();// XXXXXXX
                    position->push_back(oneDownPoint);
                    position->push_back(twoUpPoint);
                    cout << "POSITION SIZE: " << position->size() << endl; // XX logowanie, dodaj takie w każdym ifie
                    cout << "POSITION[0] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                    cout << "POSITION[1] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                }
                else if(cordToShot == oneUpPoint)
                {
                    cout << "HIT ONE UP"<< endl;
                    cout << "POSITION SIZE: " << position->size() << endl;
                    position->clear();// XXXXXXX
                    position->push_back(oneUpPoint);
                    position->push_back(twoDownPoint);
                    cout << "POSITION SIZE: " << position->size() << endl; // XX logowanie, dodaj takie w każdym ifie
                    cout << "POSITION[0] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                    cout << "POSITION[1] = " << position->front()->getShiftX() <<", " << position->front()->getShiftY() << endl;
                }
                else
                {
                    cout << "NIGDY NIE POWINNO SIE ZDARZYC" << endl;
                    cout << "CORD TO SHOOT = " << cordToShot->getShiftX() <<", " << cordToShot->getShiftY() << endl;
                }

            }

            return true;

        }

        else
        {

            cout<<"\n ustawiam miss"<< endl <<flush;
            mapPlayer->getPiece(x,y)->setState(State::MISS);
            return false;

        }



    }
}

Bot::~Bot()
{
    delete position;
}
