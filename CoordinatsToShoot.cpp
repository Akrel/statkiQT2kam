#include "CoordinatsToShoot.h"

CoordinatsToShoot :: CoordinatsToShoot  (int x, int y)
{
    this->shiftX = x;
    this->shiftY = y;


}
CoordinatsToShoot* oneLeftPoint = new CoordinatsToShoot(-1,0);
CoordinatsToShoot* twoLeftPoint = new CoordinatsToShoot(-2,0);
CoordinatsToShoot* oneRightPoint = new CoordinatsToShoot(1,0);
CoordinatsToShoot* twoRightPoint = new CoordinatsToShoot(2,0);
//gora
CoordinatsToShoot* oneUpPoint = new CoordinatsToShoot(0,-1);
CoordinatsToShoot* twoUpPoint = new CoordinatsToShoot(0,-2);
//dol
CoordinatsToShoot* oneDownPoint = new CoordinatsToShoot(0,1);
CoordinatsToShoot* twoDownPoint = new CoordinatsToShoot(0,2);

int CoordinatsToShoot :: getShiftX()
{
    return shiftX;
}


int CoordinatsToShoot :: getShiftY()
{
    return shiftY;
}
