//#############################################################################
// ARCHIVO             : clsBug.cpp
// AUTOR               : Alejandro Marcelo Tidele.
// VERSION             : v. 1.0 estable.
// FECHA DE CREACION   : 14/11/2018.
// ULTIMA ACTUALIZACION: 14/11/2018.
// LICENCIA            : GPL (General Public License) - Version 3.
//=============================================================================
// SISTEMA OPERATIVO   : Linux / Windows.
// IDE                 : Code::Blocks.
// COMPILADOR          : GNU GCC Compiler (Linux) / MinGW (Windows).
//=============================================================================
// DESCRIPCION: Este archivo contiene la definicion de los metodos de la clase
//              "clsBug".
//
//              "clsBug" consta de los metodos necesarios para administrar
//              el funcionamiento de los personajes (bichos).
//
///////////////////////////////////////////////////////////////////////////////
#include "clsBug.h"

//=============================================================================
// METODO    : fly(clsScreen* screen)
// ACCION    : Vuelo normal del personaje
// PARAMETROS: clsScreen* screen -> Puntero a la pantalla.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::fly(clsScreen* screen)
{
    this->setI(0);
    this->paste(screen->getPtr());
}

//=============================================================================
// METODO    : fly(clsScreen* screen, clsRandom* random, int maxWidth, int maxHeight)
// ACCION    : Vuelo aleatorio del enemigo
// PARAMETROS: clsScreen* screen -> Puntero a la pantalla
//             clsRandom* random -> Puntero a los eventos random
//             int maxWidth -> Tamaño maximo ancho
//             int maxHeight -> Tamaño maximo de alto
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::fly(clsScreen* screen, clsRandom* random, int maxWidth, int maxHeight)
{
    this->setI(0);
    if (this->getX() <= maxWidth && this->getX() > 0 && this->getY() > 50 && this->getY() < maxHeight) {

        int randomNumber = random->getNumber(10);
        int randomNumberX = 0;
        int randomNumberY = 0;

        randomNumberX = this->getX() + (randomNumber % 2 ? randomNumber : randomNumber * -1);
        randomNumberY = this->getY() + (randomNumber % 2 ? randomNumber : randomNumber * -1);

        if (randomNumberX > 0 && randomNumberX <= maxWidth)
            this->setX(randomNumberX);

        if (randomNumberY > 50 && randomNumberY < 500)
            this->setY(randomNumberY);

        this->paste(screen->getPtr());
    }
}

//=============================================================================
// METODO    : void move(direction dir, clsScene* scene, clsScreen* screen)
// ACCION    : Movimiento del personaje o del enemigo
// PARAMETROS: direction dir -> Direccion seleccionada
//             clsScene* scene -> Puntero a la escena
//             clsScreen* screen -> Puntero a la pantalla
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::move(direction dir, clsScene* scene, clsScreen* screen)
{
    if (this->canMove(dir, screen)) {
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

//=============================================================================
// METODO    : void fire(clsBug* enemies, clsScene* scene, clsScreen* screen, clsMusic* music)
// ACCION    : Ataque del personajes
// PARAMETROS: clsBug* enemies -> Puntero a los enemigos
//             clsScene* scene -> Puntero a la escena
//             clsScreen* screen -> Puntero a la pantalla
//             clsMusic* music -> Puntero de la musica
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::fire(clsBug* enemies, clsScene* scene, clsScreen* screen, clsMusic* music)
{
    if (! this->mucus->isAttacking()) {
        this->mucus->setAttackStatus(true);
        this->mucus->setX(this->getX() + this->mucus->getWidth());
        this->mucus->setY(this->getY() + 110);
        this->mucus->spit(music);
    }

    if (this->mucus->getX() <= (screen->getWidth() - this->mucus->getWidth() - 75) && this->mucus->isAttacking()) {
        this->paste(screen->getPtr());
        this->mucus->setX(this->mucus->getX() + this->mucus->getFireSpeed());
        this->mucus->paste(screen->getPtr());
        this->checkEnemieKilled(enemies, screen, scene);
        return;
    }

    this->mucus->setAttackStatus(false);
}

//=============================================================================
// METODO    : void enemyFire(clsBug* bug, clsScreen* screen)
// ACCION    : Ataque del enemigo
// PARAMETROS: clsBug* bug -> Puntero al personaje principal
//             clsScreen* screen -> Puntero a la pantalla
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::enemyFire(clsBug* bug, clsScreen* screen)
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

//=============================================================================
// METODO    : void die(clsScreen* screen)
// ACCION    : Muerte del personaje o del enemigo
// PARAMETROS: clsScreen* screen -> Puntero a la pantalla
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::die(clsScreen* screen)
{
    this->setY(3000);
    this->paste(screen->getPtr());
}

//=============================================================================
// METODO    : unsigned int getEvolutionLevel()
// ACCION    : Devuelve el nivel del personaje
// PARAMETROS: NADA.
// DEVUELVE  : Entero sin signo.
//-----------------------------------------------------------------------------
unsigned int clsBug::getEvolutionLevel()
{
    return this->evolutionLevel;
}

//=============================================================================
// METODO    : unsigned int getEnemiesKilled()
// ACCION    : Devuelve los enemigos aniquilados
// PARAMETROS: NADA.
// DEVUELVE  : Entero sin signo.
//-----------------------------------------------------------------------------
unsigned int clsBug::getEnemiesKilled()
{
    return this->enemiesKilled;
}

//=============================================================================
// METODO    : void setEnemiesKilled(unsigned int enemiesKilled)
// ACCION    : Establece los enemigos aniquilidos
// PARAMETROS: unsigned int enemiesKilled -> Cantidad de enemigos aniquilados
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::setEnemiesKilled(unsigned int enemiesKilled)
{
    this->enemiesKilled = enemiesKilled;
}

//=============================================================================
// METODO    : void setEvolutionLevel(unsigned int evolutionLevel)
// ACCION    : Establece el nivel del personaje principal
// PARAMETROS: unsigned int evolutionLevel -> Nivel de juego
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::setEvolutionLevel(unsigned int evolutionLevel)
{
    this->evolutionLevel = evolutionLevel;
}

//=============================================================================
// METODO    : void setSpeed(unsigned int speed)
// ACCION    : Establece la velocidad
// PARAMETROS: unsigned int speed -> Velocidad de movimiento
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::setSpeed(unsigned int speed)
{
    this->movement = speed;
}

//=============================================================================
// METODO    : bool canMove(direction dir, clsScreen* screen)
// ACCION    : Verifica si puede moverse en la dirección seleccionada
// PARAMETROS: direction dir -> Direccion seleccionada
//             clsScreen* screen -> Puntero a la pantalla
// DEVUELVE  : Booleano si puede moverse o no.
//-----------------------------------------------------------------------------
bool clsBug::canMove(direction dir, clsScreen* screen)
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

//=============================================================================
// METODO    : void checkEnemieKilled(clsBug* enemies, clsScreen* screen, clsScene* scene)
// ACCION    : Verifica si el enemigo murió
// PARAMETROS: clsBug* enemies -> Puntero a los enemigos
//             clsScreen* screen -> cantidad de millisegundos de duracion de la pausa.
//             clsScene* scene -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsBug::checkEnemieKilled(clsBug* enemies, clsScreen* screen, clsScene* scene)
{
    if (this->evolutionLevel == 7) {
        if (this->mucus->getContact(&enemies[35])) {
            this->mucus->setAttackStatus(false);
            this->mucus->setX(-50);
            this->mucus->paste(screen->getPtr());

            enemies[35].energy->setLife(enemies[35].energy->getLife() - this->energy->getDamage());

            if (enemies[35].energy->getLife() == 0) {
                enemies[35].die(screen);
                this->enemiesKilled++;
                scene->writeText(screen, this->enemiesKilled, enemies[35].getX(), enemies[35].getY() + (enemies[35].getWidth() / 2));
            }
        }

        return;
    }

    for (int i = 0; i < 35; i++) {
        if (this->mucus->getContact(&enemies[i])) {
            this->mucus->setAttackStatus(false);
            this->mucus->setX(-50);
            this->mucus->paste(screen->getPtr());

            enemies[i].energy->setLife(enemies[i].energy->getLife() - this->energy->getDamage());

            if (enemies[i].energy->getLife() == 0) {
                enemies[i].die(screen);
                this->enemiesKilled++;
                scene->writeText(screen, this->enemiesKilled, enemies[i].getX(), enemies[i].getY() + (enemies[i].getWidth() / 2));
            }

            this->energy->setEvolution(this->energy->getEvolution() + this->energy->getPlusEnergy());

            if (this->enemiesKilled > 0 && ! (bool) (this->enemiesKilled % 3)) { // Mueve bloque de 3 bichos
                for (int j = this->enemiesKilled - 1; j < 35; j++) {
                    enemies[j].setX(enemies[j].getX() - 300);
                    enemies[j].paste(screen->getPtr());
                }
            }

            if (this->energy->getEvolution() == 50) {
                this->energy->setEvolution(0);
                this->evolutionLevel++;
                this->energy->setLife(100);
                this->movement += 4;
                this->mucus->setFireSpeed(15 + (this->evolutionLevel * 2));
                for (int j = 0; j < 35; j++)
                    enemies[j].mucus->setFireSpeed(enemies[j].mucus->getFireSpeed() + 5);

            }

            if (this->evolutionLevel == 7) {
                this->energy->setEvolution(50);
            }
        }
    }
}
