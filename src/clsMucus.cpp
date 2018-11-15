//#############################################################################
// ARCHIVO             : clsMucus.cpp
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
//              "clsMucus".
//
//              "clsMucus" consta de los metodos necesarios para administrar
//              los disparos de los personajes
//
///////////////////////////////////////////////////////////////////////////////
#include "clsMucus.h"

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
clsMucus::clsMucus(bool isEnemy)
{
    this->init((isEnemy ? "IMAGES/enemies/mucus.png" : "IMAGES/bugs/mucus.png"), 50, 100);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsMucus::spit(clsMusic* music)
{
    music->playMusic(0);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
bool clsMucus::isAttacking()
{
    return this->attacking;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
unsigned int clsMucus::getFireSpeed()
{
    return fireSpeed;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsMucus::setAttackStatus(bool attacking)
{
    this->attacking = attacking;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsMucus::setFireSpeed(unsigned int fireSpeed)
{
    this->fireSpeed = fireSpeed;
}
