#include "clsMucus.h"

/*******************************************************************
*                         FUNCIONES PUBLICAS                       *
*******************************************************************/

void clsMucus::spit(clsMusic* music)
{
    music->playMusic(0);
}

void clsMucus::move(clsScreen* screen, int posX, int posY)
{
    this->setX(posX + this->getWidth());
    this->setY(posY + 110);
    this->paste(screen->getPtr());
    screen->refresh();
}
