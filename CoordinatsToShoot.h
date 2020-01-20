#ifndef PIECETOSHOOT_H
#define PIECETOSHOOT_H

class CoordinatsToShoot
{
public:

    int getShiftX();
    int getShiftY();
    CoordinatsToShoot(int x, int y);

private:


    int shiftX;
    int shiftY;
    ~CoordinatsToShoot();



};
//lewo
extern CoordinatsToShoot* oneLeftPoint;
extern CoordinatsToShoot* twoLeftPoint;
//prawo
extern CoordinatsToShoot* oneRightPoint;
extern CoordinatsToShoot* twoRightPoint;
//gora
extern CoordinatsToShoot* oneUpPoint;
extern CoordinatsToShoot* twoUpPoint;
//dol
extern CoordinatsToShoot* oneDownPoint;
extern CoordinatsToShoot* twoDownPoint;
#endif // PIECETOSHOOT_H
