//#############################################################################
// ARCHIVO             : clsBug.h
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
#ifndef CLSBUG_H
#define CLSBUG_H
#include <clsEvent.h> // Administrador de eventos de teclado y mouse
#include <clsMusic.h> // Administrador de eventos de sonido
#include <clsRandom.h> // Administrador de eventos aleatorios
#include <clsEnergy.h> // Energia de cada bicho
#include <clsMucus.h> // Moco de cada bicho
#include <clsScene.h> // Manejo de la escena

class clsBug : public clsScene
{
public:
    void fly(clsScreen*); // Vuelo normal del personaje
    void fly(clsScreen*, clsRandom*, int maxWidth = 1200, int maxHeight = 700); // Vuelo aleatorio del enemigo
    void move(direction, clsScene*, clsScreen*); // Movimiento del personaje o del enemigo
    void fire(clsBug*, clsScene*, clsScreen*, clsMusic*); // Ataque del personajes
    void enemyFire(clsBug*, clsScreen*); // Ataque del enemigo
    void die(clsScreen*); // Muerte del personaje o del enemigo
    unsigned int getEvolutionLevel(); // Devuelve el nivel del personaje
    unsigned int getEnemiesKilled(); // Devuelve los enemigos aniquilados
    void setEnemiesKilled(unsigned int); // Establece los enemigos aniquilidos
    void setEvolutionLevel(unsigned int); // Establece el nivel
    void setSpeed(unsigned int); // Establece la velocidad
    clsEnergy* energy; // Energia del personaje o de los enemigos
    clsMucus* mucus; // Moco del personajes o del enemigo

private:
    bool canMove(direction, clsScreen*); // Verifica si puede moverse en la dirección seleccionada
    void checkEnemieKilled(clsBug*, clsScreen*, clsScene*); // Verifica si el enemigo murió

protected:
    unsigned int movement = 10; // Valor de movimiento
    unsigned int evolutionLevel = 0; // Valor de nivel
    unsigned int enemiesKilled = 0; // Valor de enemigos aniquilados
};

#endif // CLSBUG_H
