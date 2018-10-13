#include "clsBug.h"

/*******************************************************************
*                         FUNCIONES PUBLICAS                       *
*******************************************************************/

void clsBug::fly(clsScreen* screen)
{
    this->setI(0);
    this->paste(screen->getPtr());
    screen->refresh();
}

void clsBug::fly(clsScreen* screen, clsScene* scene)
{
    scene->paste(screen->getPtr());
    this->setI(0);
    this->paste(screen->getPtr());
    screen->refresh();
    scene->paste(screen->getPtr());
    this->setI(1);
    this->paste(screen->getPtr());
    screen->refresh();
    scene->paste(screen->getPtr());
    this->setI(2);
    this->paste(screen->getPtr());
    screen->refresh();
    this->setI(1);
    this->paste(screen->getPtr());
    screen->refresh();
}

void clsBug::move(direction dir, clsScene* scene, clsScreen* screen)
{
    scene->move(screen);

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
    screen->refresh();
}

void clsBug::fire(clsMucus* mucus, clsScene* scene, clsScreen* screen, clsEvent* event, clsMusic* music)
{
    int posX = this->getX();
    int posY = this->getY();
    mucus->spit(music);
    while (posX <= screen->getWidth()) {
        scene->move(screen);
        this->paste(screen->getPtr());
        mucus->move(screen, posX, posY);
        posX += 15;
        if (event->wasEvent()) {
            if (event->getEventType() == KEY_PRESSED) { // Verifico si hay evento de teclado
                if (event->getKey() == KEY_a || event->getKey() == KEY_s ||
                    event->getKey() == KEY_w || event->getKey() == KEY_d ) {
                    direction dir = event->getKey() == KEY_a ? LEFT :
                                    event->getKey() == KEY_s ? DOWN :
                                    event->getKey() == KEY_d ? RIGHT : UP;
                    this->movement = 50;
                    this->move(dir, scene, screen); // Muevo el bicho
                    event->wasEvent();
                }
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
        return (posY - this->movement > 0);
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
