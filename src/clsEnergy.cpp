#include "clsEnergy.h"

clsEnergy::clsEnergy(unsigned int life)
{
    const char energies[100][100] = {
        "IMAGES/bugs/life.png",
        "IMAGES/bugs/evolution.png"};

    this->init(energies, 2, 50, 100);
    this->setLife(life);
}

void clsEnergy::updateStatusBar(clsScreen* screen, clsScene* scene, unsigned int enemiesKilled)
{
    int life = this->getLife();
    unsigned int posX = 70;
    this->setI(0);
    this->setY(12);

    for (; life > 0 && life <= 170; life -= 5) {
        this->setX(posX);
        this->paste(screen->getPtr());
        posX += 20;
    }

    int evolution = this->getEvolution();
    posX = 895;
    this->setI(1);
    this->setY(12);

    for (; evolution > 0 && evolution <= 50; evolution -= 5) {
        this->setX(posX);
        this->paste(screen->getPtr());
        posX += 20;
        this->setX(posX);
        this->paste(screen->getPtr());
        posX += 20;
    }

    scene->addKill(screen, enemiesKilled, 500, 15);
}

unsigned int clsEnergy::getDamage()
{
    return this->damage;
}

int clsEnergy::getEvolution()
{
    return this->evolution;
}

unsigned int clsEnergy::getPlusEnergy()
{
    return this->plusEnergy;
}

int clsEnergy::getLife()
{
    return this->life;
}

void clsEnergy::setEvolution(int evolution)
{
    this->evolution = evolution;
}

void clsEnergy::setLife(int life)
{
    this->life = life;
}
