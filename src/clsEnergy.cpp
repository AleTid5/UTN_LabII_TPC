#include "clsEnergy.h"

clsEnergy::clsEnergy()
{
    const char energies[100][100] = {
        "IMAGES/bugs/life.png",
        "IMAGES/bugs/evolution.png"};

    this->init(energies, 2, 50, 100);
}

void clsEnergy::updateLife(clsScreen* screen)
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
}

void clsEnergy::updateEvolution(clsScreen* screen)
{
    int evolution = this->getEvolution();
    unsigned int posX = 895;
    this->setI(1);
    this->setY(12);

    for (; evolution > 0 && evolution <= 50; evolution -= 5) {
        this->setX(posX);
        this->paste(screen->getPtr());
        posX += 40;
    }
}

int clsEnergy::getEvolution()
{
    return this->evolution;
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
