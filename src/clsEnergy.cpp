#include "clsEnergy.h"

clsEnergy::clsEnergy(unsigned int life)
{
    const char energies[100][100] = {
        "IMAGES/bugs/life.png",
        "IMAGES/bugs/evolution.png",
        "IMAGES/bugs/bossLife.png"};

    this->init(energies, 3, 50, 100);
    this->setLife(life);
}

void clsEnergy::updateStatusBar(clsScreen* screen, clsScene* scene, unsigned int enemiesKilled, int bossLife)
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

    posX = 895;

    if (enemiesKilled == 35) {
        this->setI(2);
        scene->writeText(screen, bossLife, 1300, 15);
        for (; bossLife > 0; bossLife -= 5) {
            this->setX(posX);
            this->paste(screen->getPtr());
            posX += 4;
        }
    } else {
        int evolution = this->getEvolution();
        this->setI(1);
        for (; evolution > 0 && evolution <= 50; evolution -= 5) {
            this->setX(posX);
            this->paste(screen->getPtr());
            posX += 20;
            this->setX(posX);
            this->paste(screen->getPtr());
            posX += 20;
        }
    }
    scene->writeText(screen, enemiesKilled, 500, 27);
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

void clsEnergy::setDamage(unsigned int damage)
{
    this->damage = damage;
}

void clsEnergy::setEvolution(int evolution)
{
    this->evolution = evolution;
}

void clsEnergy::setLife(int life)
{
    this->life = life;
}
