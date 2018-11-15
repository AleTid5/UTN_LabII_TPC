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
// METODO    : clsMucus(bool isEnemy)
// ACCION    : Constructor del objeto de moco
// PARAMETROS: bool isEnemy -> Determina si es un personaje de tipo enemigo.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
clsMucus::clsMucus(bool isEnemy)
{
    this->init((isEnemy ? "IMAGES/enemies/mucus.png" : "IMAGES/bugs/mucus.png"), 50, 100);
}

//=============================================================================
// METODO    : bool isAttacking()
// ACCION    : Devuelve si hay un ataque en curso
// PARAMETROS: clsMusic* music -> Puntero de musica.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsMucus::spit(clsMusic* music)
{
    music->playMusic(0);
}

//=============================================================================
// METODO    : void spit(clsMusic*)
// ACCION    : Realiza el sonido de escupitajo
// PARAMETROS: NADA.
// DEVUELVE  : Booleano si está atacando.
//-----------------------------------------------------------------------------
bool clsMucus::isAttacking()
{
    return this->attacking;
}

//=============================================================================
// METODO    : unsigned int getFireSpeed()
// ACCION    : Devuelve la velocidad actual de disparo
// PARAMETROS: NADA.
// DEVUELVE  : Entero sin signo de velocidad de disparo.
//-----------------------------------------------------------------------------
unsigned int clsMucus::getFireSpeed()
{
    return fireSpeed;
}

//=============================================================================
// METODO    : void setAttackStatus(bool)
// ACCION    : Establece el estado de ataque en curso
// PARAMETROS: bool attacking -> Estado de ataque.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsMucus::setAttackStatus(bool attacking)
{
    this->attacking = attacking;
}

//=============================================================================
// METODO    : void setFireSpeed(unsigned int)
// ACCION    : Establece la velocidad de disparo
// PARAMETROS: unsigned int fireSpeed -> Velocidad de disparo.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsMucus::setFireSpeed(unsigned int fireSpeed)
{
    this->fireSpeed = fireSpeed;
}
