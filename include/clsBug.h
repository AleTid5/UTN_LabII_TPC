#ifndef CLSBUG_H
#define CLSBUG_H
#include <clsEvent.h>
#include <clsMusic.h>
#include <clsEnergy.h>
#include <clsMucus.h>
#include <clsRandom.h>
#include <clsScene.h>

class clsBug : public clsScene
{
public:
    void fly(clsScreen*);
    void fly(clsScreen*, clsRandom*);
    void move(direction, clsScene*, clsScreen*);
    void fire(clsBug*, clsScene*, clsScreen*, clsEvent*, clsMusic*, clsRandom*);
    void enemyFire(clsBug*, clsScene*, clsScreen*, clsMusic*);
    void die(clsScreen*);
    unsigned int getEnemiesKilled();
    unsigned int getEvolutionLevel();
    clsEnergy* energy;
    clsMucus* mucus;

private:
    bool canMove(direction, clsScene*, clsScreen*);
    void checkEnemieKilled(clsBug*, clsScreen*, clsScene*, int, int &posY);

protected:
    unsigned int movement = 5;
    unsigned int evolutionLevel = 0;
    unsigned int enemiesKilled = 0;
};

#endif // CLSBUG_H
