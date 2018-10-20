#include "clsBug.h"

/*******************************************************************
*                         FUNCIONES PUBLICAS                       *
*******************************************************************/

void clsBug::fly(clsScreen* screen)
{
    this->setI(this->evolution);
    this->paste(screen->getPtr());
}

void clsBug::move(direction dir, clsScene* scene, clsScreen* screen)
{
    scene->move(screen);
    this->energy->updateLife(screen);
    this->energy->updateEvolution(screen);

    if (this->canMove(dir, scene, screen)) {
        if (dir == UP)
            this->setY(this->getY() - this->movement);
        if (dir == DOWN)
            this->setY(this->getY() + this->movement);
        if (dir == LEFT)
            this->setX(this->getX() - this->movement);
        if (dir == RIGHT)
            this->setX(this->getX() + this->movement);
    }

    this->paste(screen->getPtr());
}

void clsBug::fire(clsMucus* mucus, clsScene* scene, clsScreen* screen, clsEvent* event, clsMusic* music)
{
    int posX = this->getX();
    int posY = this->getY();
    mucus->spit(music);
    while (posX <= screen->getWidth()) {
        scene->move(screen);
        this->energy->updateLife(screen);
        this->energy->updateEvolution(screen);
        this->paste(screen->getPtr());
        mucus->move(screen, posX, posY);
        posX += 15;
        if (event->wasEvent()) {
            while (event->getEventType() == KEY_PRESSED &&
                    (event->getKey() == KEY_a || event->getKey() == KEY_s ||
                     event->getKey() == KEY_w || event->getKey() == KEY_d)) { // Verifico si hay evento de teclado

                direction dir = event->getKey() == KEY_a ? LEFT :
                                event->getKey() == KEY_s ? DOWN :
                                event->getKey() == KEY_d ? RIGHT : UP;

                mucus->move(screen, posX, posY);
                posX += 15;
                this->move(dir, scene, screen); // Muevo el bicho

                event->wasEvent();
            }
        }
    }

    this->movement = 5;
}

/*******************************************************************
*                         FUNCIONES PRIVADAS                       *
*******************************************************************/

bool clsBug::canMove(direction dir, clsScene* scene, clsScreen* screen)
{
    unsigned int width = screen->getWidth();
    unsigned int height = screen->getHeight();
    unsigned int posX = this->getX();
    unsigned int posY = this->getY();

    if (dir == UP) {
        return (posY - this->movement > 53);
    }

    if (dir == DOWN) {
        posY += this->getHeight();
        return (posY + this->movement < height);
    }

    if (dir == LEFT) {
        return (posX - this->movement > 0);
    }

    if (dir == RIGHT) {
        posX += this->getWidth();
        return (posX + this->movement < width);
    }

    return false;
}
