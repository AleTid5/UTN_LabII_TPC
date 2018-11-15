//#############################################################################
// ARCHIVO             : clsEnergy.h
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
#ifndef CLSENERGY_H
#define CLSENERGY_H
#include <clsScene.h> // Manejo de la escena

class clsEnergy : public clsScene
{
    public:
        clsEnergy(unsigned int life); // Constructor de energia
        void updateStatusBar(clsScreen*, clsScene*, unsigned int, int); // Actualiza el tablero de energia
        int getEvolution(); // Devuelve la energia de evolución
        int getLife(); // Devuelve la energia de vida
        unsigned int getDamage(); // Devuelve el daño que realizan los personajes
        unsigned int getPlusEnergy(); // Devuelve el aumento de energia evolutiva
        void setDamage(unsigned int); // Establece el daño que realizan los personajes
        void setEvolution(int); // Establece la energia de evolución
        void setLife(int); // Establece la energia de vida

    private:
        int life; // Energia de los personajes
        int evolution; // Energia de evolucion de los personajes
        unsigned int damage = 25; // Daño que realizan los personajes
        unsigned const int plusEnergy = 10; // Aumento de energia evolutiva
};

#endif // CLSENERGY_H
