//#############################################################################
// ARCHIVO             : clsMucus.h
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
#ifndef CLSMUCUS_H
#define CLSMUCUS_H
#include <clsAudio.h> // Administracion de audio
#include <clsMusic.h> // Administracion de musica
#include <clsScene.h> // Manejo de la escena

class clsMucus : public clsScene
{
public:
    clsMucus(bool isEnemy = false); // Constructor del objeto de moco
    bool isAttacking(); // Devuelve si hay un ataque en curso
    void spit(clsMusic*); // Realiza el sonido de escupitajo
    unsigned int getFireSpeed(); // Devuelve la velocidad actual de disparo
    void setAttackStatus(bool); // Establece el estado de ataque en curso
    void setFireSpeed(unsigned int); // Establece la velocidad de disparo

private:
    bool attacking = false; // Determina si hay un ataque en curso
    unsigned int fireSpeed = 10; // Velocidad de disparo
};

#endif // MUCUS_H

