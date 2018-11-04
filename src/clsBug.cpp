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

    if (this->getX() <= 1200 && this->getX() > 0 && this->getY() > 50 && this->getY() < 700) {

        int randomNumber = random->getNumber(10);
        int randomNumberX = 0;
        int randomNumberY = 0;

        randomNumberX = this->getX() + (randomNumber % 2 ? randomNumber : randomNumber * -1);
        randomNumberY = this->getY() + (randomNumber % 2 ? randomNumber : randomNumber * -1);

        if (randomNumberX > 0 && randomNumberX <= 1200)
            this->setX(randomNumberX);

        if (randomNumberY > 50 && randomNumberY < 500)
            this->setY(randomNumberY);

        this->paste(screen->getPtr());
    }
}

void clsBug::move(direction dir, clsScene* scene, clsScreen* screen)
{
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
    if (! this->mucus->isAttacking()) {
            this->mucus->setAttackStatus(true);
            this->mucus->setX(this->getX() + this->mucus->getWidth());
            this->mucus->setY(this->getY() + 110);
            this->mucus->spit(music);
    }

    if (this->mucus->getX() <= (screen->getWidth() - this->mucus->getWidth() - 75) && this->mucus->isAttacking()) {
        this->energy->updateStatusBar(screen, scene, this->getEnemiesKilled());
        this->paste(screen->getPtr());
        this->mucus->setX(this->mucus->getX() + 15);
        this->mucus->paste(screen->getPtr());
        this->checkEnemieKilled(enemies, screen, scene);
        return;
    }

    this->mucus->setAttackStatus(false);
}

void clsBug::enemyFire(clsBug* bug, clsScene* scene, clsScreen* screen, clsMusic* music)
{
    if (this->getX() < 1200 && this->getX() > 0 && this->getY() > 50 && this->getY() < 750) {
        if (! this->mucus->isAttacking() && ((bug->getY() - 50) <= this->getY() && (bug->getY() + 50) >= this->getY())) {
            this->mucus->setAttackStatus(true);
            this->mucus->setX(this->getX() - 100);
            this->mucus->setY(this->getY() + 80);
        }

        if (this->mucus->isAttacking()) {
            this->mucus->setX(this->mucus->getX() - this->mucus->getFireSpeed());
            this->mucus->paste(screen->getPtr());

            bool contact = this->mucus->getContact(bug);

            if (contact) {
                bug->energy->setLife(bug->energy->getLife() - this->energy->getDamage());
                this->mucus->setX(-500);
                this->mucus->paste(screen->getPtr());
            }

            if (contact || this->mucus->getX() <= 0)
                this->mucus->setAttackStatus(false);
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

void clsBug::setEnemiesKilled(unsigned int enemiesKilled)
{
    this->enemiesKilled = enemiesKilled;
}

void clsBug::setEvolutionLevel(unsigned int evolutionLevel)
{
    this->evolutionLevel = evolutionLevel;
}

void clsBug::setSpeed(unsigned int speed)
{
    this->movement = speed;
}

/*******************************************************************
*                         FUNCIONES PRIVADAS                       *
*******************************************************************/

bool clsBug::canMove(direction dir, clsScene* scene, clsScreen* screen)
{
    int posX = this->getX();
    int posY = this->getY();
    bool canMove = false;

    if (dir == UP) {
        canMove = (int) (posY - this->movement) >= 53;
        if (! canMove) this->setY(53);
        return canMove;
    }

    if (dir == DOWN) {
        int height = screen->getHeight();
        posY += this->getHeight();
        canMove = (posY + this->movement) < (unsigned int) height;
        if (! canMove) this->setY(height - this->getHeight());
        return canMove;
    }

    if (dir == LEFT) {
        canMove = (int) (posX - this->movement) >= 0;
        if (! canMove) this->setX(0);
        return canMove;
    }

    if (dir == RIGHT) {
        int width = screen->getWidth();
        posX += this->getWidth();
        canMove = (posX + this->movement) < (unsigned int) width;
        if (! canMove) this->setX(width - this->getWidth());
        return canMove;
    }

    return canMove;
}

void clsBug::checkEnemieKilled(clsBug* enemies, clsScreen* screen, clsScene* scene)
{
    for (int i = 0; i < 35; i++) {
        if (this->mucus->getContact(&enemies[i])) {
            this->mucus->setAttackStatus(false);
            this->mucus->setX(-50);
            this->mucus->paste(screen->getPtr());

            enemies[i].energy->setLife(enemies[i].energy->getLife() - this->energy->getDamage());

            if (enemies[i].energy->getLife() == 0) {
                enemies[i].die(screen);
                this->enemiesKilled++;
                scene->addKill(screen, this->enemiesKilled, enemies[i].getX(), enemies[i].getY() + (enemies[i].getWidth() / 2));
            }

            this->energy->setEvolution(this->energy->getEvolution() + this->energy->getPlusEnergy());

            if (this->enemiesKilled > 0 && ! (bool) (this->enemiesKilled % 3)) { // Mueve bloque de 3 bichos
                for (int j = this->enemiesKilled - 1; j < 35; j++) {
                    enemies[j].setX(enemies[j].getX() - 300);
                    enemies[j].paste(screen->getPtr());
                }
            }

            if (this->energy->getEvolution() == 50 && this->evolutionLevel < 7) {
                this->energy->setEvolution(0);
                this->evolutionLevel++;
                this->energy->setLife(100);
                this->movement += 10;
                for (int j = 0; j < 35; j++)
                    enemies[j].mucus->setFireSpeed(enemies[j].mucus->getFireSpeed() + 5);

            }
        }
    }
}
