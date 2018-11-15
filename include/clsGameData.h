//#############################################################################
// ARCHIVO             : clsGameData.h
// AUTOR               : Alejandro Marcelo Tidele.
// VERSION             : v. 1.0 estable.
// FECHA DE CREACION   : 14/11/2018.
// ULTIMA ACTUALIZACION: 14/11/2018.          .
// LICENCIA            : GPL (General Public License) - Version 3.
//=============================================================================
// SISTEMA OPERATIVO   : Linux / Windows.
// IDE                 : Code::Blocks.
// COMPILADOR          : GNU GCC Compiler (Linux) / MinGW (Windows).
//=============================================================================
// DESCRIPCION: Este archivo contiene la definicion de los metodos de la clase
//              "clsGameData".
//
//              "clsGameData" consta de los metodos necesarios para salvaguardar
//              la información necesaria del juego (partida y puntaje/s)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CLSGAMEDATA_H
#define CLSGAMEDATA_H

#include <stdio.h> // Libreria de manejo de entrada y salida standard
#include <clsBug.h> // Manejo de los personajes

class clsGameData
{
    public:
    int enemiesKilled = 0; // Enemigos aniquilados
    int evolutionEnergy = 0; // Energia de evolucion
    int life = 100; // Energia de vida
    int time = 0; // Tiempo de juego
    int enemies[36][2]; // Matriz de posicion X-Y de los enemigos
    int bossLife; // Vida del jefe
    char playierName[5]; // Nombre del jugador
    bool wasRead = false; // Verifica si el archivo fue leido
    void arrangedSave(const char*, const char*); // Funcion que guarda los datos arreglados (Ascendente por puntos)
    void save(const char*, const char*); // Funcion que guarda los datos ingresados
    void read(const char*, const char*); // Funcion que lee el archivo 1 vez
    void read(const char*, const char*, unsigned int); // Funcion que lee el archivo N veces
    void removeFile(const char*); // Funcion que elimina el archivo
};

#endif // CLSGAMEDATA_H
