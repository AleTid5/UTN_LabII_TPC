//#############################################################################
// ARCHIVO             : clsPressableKey.cpp
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
//              "clsPressableKey".
//
//              "clsPressableKey" consta de los metodos necesarios para administrar
//              las teclas presionadas por el usuario.
//
///////////////////////////////////////////////////////////////////////////////
#include "clsPressableKey.h"

//=============================================================================
// METODO    : void operator=(int)
// ACCION    : Establece que tecla fue presionada
// PARAMETROS: int pressedKey -> Tecla presionada.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsPressableKey::operator=(int pressedKey) {
    this->pressedKey = pressedKey;
}

//=============================================================================
// METODO    : void operator>(bool)
// ACCION    : Establece el estado de presion de la tecla
// PARAMETROS: bool isPressed -> Estado de presión de tecla.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsPressableKey::operator>(bool isPressed) {
    this->isPressed = isPressed;
}

//=============================================================================
// METODO    : bool isKeyPressed()
// ACCION    : Devuelve el estado de la tecla
// PARAMETROS: NADA.
// DEVUELVE  : Booleano si la tecla está presionada.
//-----------------------------------------------------------------------------
bool clsPressableKey::isKeyPressed() {
    return this->isPressed;
}

//=============================================================================
// METODO    : int getKey()
// ACCION    : Devuelve la tecla
// PARAMETROS: NADA.
// DEVUELVE  : Entero del valor de la tecla.
//-----------------------------------------------------------------------------
int clsPressableKey::getKey() {
    return this->pressedKey;
}
