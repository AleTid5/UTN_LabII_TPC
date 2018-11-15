//#############################################################################
// ARCHIVO             : clsPressableKey.h
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
#ifndef CLSPRESSABLEKEY_H
#define CLSPRESSABLEKEY_H

class clsPressableKey
{
    public:
        void operator=(int); // Establece que tecla fue presionada
        void operator>(bool); // Establece el estado de presion de la tecla
        bool isKeyPressed(); // Devuelve el estado de la tecla
        int getKey(); // Devuelve la tecla

    protected:

    private:
        int pressedKey; // Valor en entero de la tecla presionada
        bool isPressed = false; // Valor del estado de la tecla
};

#endif // CLSPRESSABLEKEY_H
