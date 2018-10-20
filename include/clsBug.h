#ifndef CLSBUG_H
#define CLSBUG_H
#include <clsEvent.h>
#include <clsMusic.h>
#include <clsEnergy.h>
#include <clsMucus.h>
#include <clsScene.h>

class clsBug : public clsScene
{
public:
    void fly(clsScreen*);
    void fly(clsScreen*, clsScene*);
    void move(direction, clsScene*, clsScreen*);
    void fire(clsMucus*, clsScene*, clsScreen*, clsEvent*, clsMusic*);
    clsEnergy* energy;
    clsMucus* mucus;

private:
    bool canMove(direction, clsScene*, clsScreen*);

protected:
    unsigned int movement = 5;
    unsigned int evolution = 0;
};

#endif // CLSBUG_H
