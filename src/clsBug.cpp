#include "clsBug.h"

/*******************************************************************
*                         FUNCIONES PUBLICAS                       *
*******************************************************************/

void clsBug::move(direction dir, clsScene* scene, clsScreen* screen)
{
    if (this->canMove(dir, scene, screen)) {
        scene->paste(screen->getPtr());

        if (dir == UP)
            this->setY(this->getY() - this->movement);
        if (dir == DOWN)
            this->setY(this->getY() + this->movement);
        if (dir == LEFT)
            this->setX(this->getX() - this->movement);
        if (dir == RIGHT)
            this->setX(this->getX() + this->movement);

        this->paste(screen->getPtr());
        screen->refresh();
    }
}

void clsBug::fire(clsMucus* mucus, clsScene* scene, clsScreen* screen, clsEvent* event, clsMusic* music)
{
    int posX = this->getX();
    while (posX <= screen->getWidth()) {
        scene->paste(screen->getPtr());
        this->paste(screen->getPtr());
        mucus->setX(posX + this->getWidth());
        mucus->setY(this->getY() + 110);
        mucus->paste(screen->getPtr());
        screen->refresh();
        if (posX == this->getX()) mucus->spit(music);
        posX += 25;
        if (event->wasEvent()) {
            if (event->getEventType() == KEY_PRESSED) { // Verifico si hay evento de teclado
                if (event->getKey() == KEY_a || event->getKey() == KEY_s ||
                    event->getKey() == KEY_w || event->getKey() == KEY_d ) {
                    direction dir = event->getKey() == KEY_a ? LEFT :
                                    event->getKey() == KEY_s ? DOWN :
                                    event->getKey() == KEY_d ? RIGHT : UP;
                    this->movement = 25;
                    this->move(dir, scene, screen); // Muevo el bicho
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
