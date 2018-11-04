#include "clsMucus.h"

/*******************************************************************
*                         FUNCIONES PUBLICAS                       *
*******************************************************************/
clsMucus::clsMucus()
{
    this->init("IMAGES/bugs/mucus.png", 50, 100);
}

void clsMucus::spit(clsMusic* music)
{
    music->playMusic(0);
}

bool clsMucus::isAttacking()
{
    return this->attacking;
}

unsigned int clsMucus::getFireSpeed()
{
    return fireSpeed;
}

void clsMucus::setAttackStatus(bool attacking)
{
    this->attacking = attacking;
}

void clsMucus::setFireSpeed(unsigned int fireSpeed)
{
    this->fireSpeed = fireSpeed;
}
