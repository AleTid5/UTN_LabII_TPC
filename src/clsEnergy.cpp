//#############################################################################
// ARCHIVO             : clsEnergy.cpp
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
//              "clsEnergy".
//
//              "clsEnergy" consta de los metodos necesarios para administrar
//              la energia de los personajes.
//
///////////////////////////////////////////////////////////////////////////////
#include "clsEnergy.h"

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
clsEnergy::clsEnergy(unsigned int life)
{
    const char energies[100][100] = {
        "IMAGES/bugs/life.png",
        "IMAGES/bugs/evolution.png",
        "IMAGES/bugs/bossLife.png"};

    this->init(energies, 3, 50, 100);
    this->setLife(life);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
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

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
unsigned int clsEnergy::getDamage()
{
    return this->damage;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
int clsEnergy::getEvolution()
{
    return this->evolution;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
unsigned int clsEnergy::getPlusEnergy()
{
    return this->plusEnergy;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
int clsEnergy::getLife()
{
    return this->life;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEnergy::setDamage(unsigned int damage)
{
    this->damage = damage;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEnergy::setEvolution(int evolution)
{
    this->evolution = evolution;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEnergy::setLife(int life)
{
    this->life = life;
}
