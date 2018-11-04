#ifndef CLSMUCUS_H
#define CLSMUCUS_H
#include <clsScene.h>
#include <clsAudio.h>
#include <clsMusic.h>

class clsMucus : public clsScene
{
public:
    clsMucus();
    bool isAttacking();
    void spit(clsMusic*);
    unsigned int getFireSpeed();
    void setAttackStatus(bool);
    void setFireSpeed(unsigned int);

private:
    bool attacking = false;
    unsigned int fireSpeed = 5;

protected:

};

#endif // MUCUS_H

