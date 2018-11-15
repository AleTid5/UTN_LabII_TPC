//#############################################################################
// ARCHIVO             : clsGameData.cpp
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
//              "clsGameData".
//
//              "clsGameData" consta de los metodos necesarios para salvaguardar
//              la información necesaria del juego (partida y puntaje/s)
//
///////////////////////////////////////////////////////////////////////////////
#include "clsGameData.h"

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsGameData::arrangedSave(const char * filename, const char * mode) {
    FILE * file;
    file = fopen(filename, mode);
    fwrite(this, sizeof * this, 1, file);
    int games = (int) (ftell(file) / sizeof * this);
    fclose(file);

    clsGameData auxData[games];
    file = fopen(filename, "rb");
    for (int i = 0; i < games && fread(&auxData[i], sizeof * this, 1, file); i++);
    fclose(file);
    this->removeFile(filename);

    for (int i = 0; i < games - 1; i++) {
        for (int j = 0; j < games - i - 1; j++) {
            int points1 = ((auxData[j].enemiesKilled + 1) * 1300) + (auxData[j].enemiesKilled == 0 ? auxData[j].time : auxData[j].time * -1);
            int points2 = ((auxData[j + 1].enemiesKilled + 1) * 1300) + (auxData[j + 1].enemiesKilled == 0 ? auxData[j + 1].time : auxData[j + 1].time * -1);
            if (points2 > points1) {
                clsGameData aux = auxData[j];
                auxData[j] = auxData[j + 1];
                auxData[j + 1] = aux;
            }
        }
    }

    file = fopen(filename, mode);
    for (int i = 0; i < games; i++) {
        fwrite(&auxData[i], sizeof * this, 1, file);
    }

    fclose(file);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsGameData::save(const char * filename, const char * mode) {
    FILE * file;
    file = fopen(filename, mode);
    fwrite(this, sizeof * this, 1, file);
    fclose(file);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsGameData::read(const char * filename, const char * mode) {
    FILE * file;
    file = fopen(filename, mode);
    if (file == NULL)
        return;
    this->wasRead = (bool) fread(this, sizeof * this, 1, file);
    fclose(file);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsGameData::read(const char * filename, const char * mode, unsigned int position) {
    FILE * file;
    file = fopen(filename, mode);
    if (file == NULL)
        return;
    fseek(file, (sizeof * this) * position, 0);
    this->wasRead = (bool) fread(this, sizeof * this, 1, file);
    fclose(file);
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsGameData::removeFile(const char * file) {
    remove(file);
}
