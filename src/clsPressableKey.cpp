//#############################################################################
// ARCHIVO             : clsPressableKey.cpp
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
//              "clsPressableKey".
//
//              "clsPressableKey" consta de los metodos necesarios para administrar
//              las teclas presionadas por el usuario.
//
///////////////////////////////////////////////////////////////////////////////
#include "clsPressableKey.h"

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsPressableKey::operator=(int pressedKey) {
    this->pressedKey = pressedKey;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsPressableKey::operator>(bool isPressed) {
    this->isPressed = isPressed;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
bool clsPressableKey::isKeyPressed() {
    return this->isPressed;
}

//=============================================================================
// METODO    : void wait(int mls)
// ACCION    : Hace una pausa de la cantidad de milisegundos establecidos como
//             parametro.
// PARAMETROS: int mls -> cantidad de millisegundos de duracion de la pausa.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
int clsPressableKey::getKey() {
    return this->pressedKey;
}
