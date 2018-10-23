#include "clsBug.h"

/*******************************************************************
*                         FUNCIONES PUBLICAS                       *
*******************************************************************/

void clsBug::fly(clsScreen* screen)
{
    //this->setI(this->evolutionLevel);
    this->setI(0);
    this->paste(screen->getPtr());
}

void clsBug::fly(clsScreen* screen, clsRandom* random)
{
    this->setI(0);

    if (this->getX() <= 1200 && this->getX() > 0 && this->getY() > 50 && this->getY() < 750) {

        int randomNumber = random->getNumber(3);
        int randomNumberX = 0;
        int randomNumberY = 0;

        randomNumberX = this->getX() + (randomNumber % 2 ? randomNumber : randomNumber * -1);
        randomNumberY = this->getY() + (randomNumber % 2 ? randomNumber : randomNumber * -1);

        if (randomNumberX > 0 && randomNumberX <= 1200)
            this->setX(randomNumberX);

        if (randomNumberY > 50 && randomNumberY < 750)
            this->setY(randomNumberY);

        this->paste(screen->getPtr());
    }
}

void clsBug::move(direction dir, clsScene* scene, clsScreen* screen)
{
    scene->move(screen);
    this->energy->updateStatusBar(screen, scene, this->getEnemiesKilled());

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

void clsBug::fire(clsBug* enemies, clsScene* scene, clsScreen* screen, clsEvent* event, clsMusic* music, clsRandom* random)
{
    int posX = this->getX();
    int posY = this->getY();
    this->mucus->spit(music);
    while (posX <= screen->getWidth() - this->mucus->getWidth() - 75) {
        scene->move(screen);

        for (int i = 0; i < 35; i++) {
            enemies[i].fly(screen, random);
            enemies[i].enemyFire(this, scene, screen, music);
        }

        this->energy->updateStatusBar(screen, scene, this->getEnemiesKilled());
        this->paste(screen->getPtr());
        this->mucus->move(screen, posX, posY);
        this->checkEnemieKilled(enemies, screen, scene, posX, posY);

        posX += 15;
        if (event->wasEvent()) {
            while (event->getEventType() == KEY_PRESSED &&
                    posX <= screen->getWidth() - this->mucus->getWidth() - 75) { // Verifico si hay evento de teclado

                if (event->getKey() != KEY_a && event->getKey() != KEY_s &&
                        event->getKey() != KEY_w && event->getKey() != KEY_d)
                    break; // Si no es de movimiento

                direction dir = event->getKey() == KEY_a ? LEFT :
                                event->getKey() == KEY_s ? DOWN :
                                event->getKey() == KEY_d ? RIGHT:
                                event->getKey() == KEY_w ? UP : INVALID;

                this->mucus->move(screen, posX, posY);
                this->checkEnemieKilled(enemies, screen, scene, posX, posY);
                posX += 15;
                this->move(dir, scene, screen); // Muevo el bicho

                for (int i = 0; i < 35; i++) {
                    enemies[i].fly(screen, random);
                    enemies[i].enemyFire(this, scene, screen, music);
                }

                event->wasEvent();
            }
        }
    }

    this->movement = 5;
}

void clsBug::enemyFire(clsBug* bug, clsScene* scene, clsScreen* screen, clsMusic* music)
{
    if (this->getX() < 1200 && this->getX() > 0 && this->getY() > 50 && this->getY() < 750) {
        if (this->mucus->getX() > 0 && this->mucus->getX() <= 1200)
            this->mucus->setX(this->mucus->getX() - 5);
        else
            this->mucus->setX(this->getX());

        this->mucus->paste(screen->getPtr());

        if (this->mucus->getContact(bug)) {
            this->mucus->setX(-200);
            bug->energy->setLife(bug->energy->getLife() - this->energy->getDamage());
        }
    }
}

void clsBug::die(clsScreen* screen)
{
    this->setY(3000);
    this->paste(screen->getPtr());
}

unsigned int clsBug::getEvolutionLevel()
{
    return this->evolutionLevel;
}

unsigned int clsBug::getEnemiesKilled()
{
    return this->enemiesKilled;
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

void clsBug::checkEnemieKilled(clsBug* enemies, clsScreen* screen, clsScene* scene, int posX, int &posY)
{
    for (int i = 0; i < 35; i++) {
        if (this->mucus->getContact(&enemies[i])) {
            posY = 4500;
            this->mucus->move(screen, posX, posY);
            enemies[i].energy->setLife(enemies[i].energy->getLife() - this->energy->getDamage());

            if (enemies[i].energy->getLife() == 0) {
                enemies[i].die(screen);
                this->enemiesKilled++;
                scene->addKill(screen, this->enemiesKilled, enemies[i].getX(), enemies[i].getY() + (enemies[i].getWidth() / 2));
            }

            this->energy->setEvolution(this->energy->getEvolution() + this->energy->getPlusEnergy());

            if (this->enemiesKilled > 0 && ! (bool) (this->enemiesKilled % 3)) {
                for (int j = this->enemiesKilled - 1; j < 35; j++) {
                    enemies[j].setX(enemies[j].getX() - 300);
                    enemies[j].paste(screen->getPtr());
                }
            }

            if (this->energy->getEvolution() == 50 && this->evolutionLevel < 7) {
                this->energy->setEvolution(0);
                this->evolutionLevel++;
                this->energy->setLife(100);
            }
        }
    }
}
