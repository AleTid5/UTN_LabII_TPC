//#############################################################################
// ARCHIVO             : clsScene.h
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
//              "clsScene".
//
//              "clsScene" consta de los metodos necesarios para administrar
//              el manejo de la escena del juego.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CLSSCENE_H
#define CLSSCENE_H
#include <clsSprite.h> // Administración de Sprites
#include <clsText.h> // Administración de los textos
#include <clsTimer.h> // Administración del tiempo de juego
#include <stdio.h> // Libreria de manejo estandar de entrada y salida

class clsScene : public clsSprite
{
public:
    int init(const char*, unsigned int posX = 0, unsigned int posY = 0); // Inicia una sola imagen
    int init(const char path[100][100], unsigned int, unsigned int posX = 0, unsigned int posY = 0); // Inicia varias imagenes al mismo tiempo
    int initText(); // Inicia el modo texto
    void writeText(clsScreen*, unsigned int, unsigned int, unsigned int); // Escribe un texto de valor entero
    void writeText(clsScreen*, const char*, unsigned int, unsigned int); // Escribe un texto de valor caracteres
    void loadWallpaper(clsScreen*, clsEvent*); // Carga el Wallpaper principal
    void move(clsScreen*); // Mueve la escena de fondo
    void startTimer(); // Inicia el tiempo de partida
    void showTimer(clsScreen*); // Muestra el tiempo de partida
    void showMenu(clsScreen*); // Muestra el menu principal
    int getTime(); // Devuelve el tiempo de partida
    void setTime(int); // Establece el tiempo de partida
    int getOptionSelected(); // Devuelve la opción seleccionada en el menú principal
    clsTimer timer; // Manejo del tiempo

protected:
    void inherit() {}; // Extensión de la clase padre que es abstracta

private:
    clsText text; // Manejo de los textos
    void dispatchOption(clsScene*, clsScreen*); // Establece la opcion a seleccionar en el menu principal
    int optionSelected; // Valor de la opcion seleccionada en el menu principal
};

#endif // CLSSCENE_H
