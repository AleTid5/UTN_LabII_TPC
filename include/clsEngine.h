//#############################################################################
// ARCHIVO             : clsEngine.h
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
//              "clsEngine".
//
//              "clsEngine" consta de los metodos necesarios para administrar
//              el motor del juego en su totalidad.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CLSENGINE_H
#define CLSENGINE_H
#include <adnConsts.h> // Tipos de datos del sistema adn-X.
#include <clsAudio.h> // Administrador de audio
#include <clsError.h> // Administrador de errores
#include <clsEvent.h> // Administrador de eventos
#include <clsMode.h> // Administrador del modo grafico
#include <clsMusic.h> // Administrador de musica
#include <clsRandom.h> // Administrador de eventos aleatorios
#include <clsScreen.h> // Administrador del monitor de video
#include <clsText.h> // Administrador de textos en modo grafico
#include <clsPressableKey.h> // Administrador de teclas presionadas
#include <clsScene.h> // Manejo de la escena
#include <clsGameData.h> // Manejo del guardado de los datos del juego
#include <clsBug.h> // Manejo de los personajes del juego

class clsEngine
{
public:
    void init(); // Inicio del motor
    void run(bool playAgain = false); // Vida del motor
    void keyCommand(); // Manejo de las teclas presionadas
    void stopRun(); // Manejo al dejar de jugar
    void comeBackSoon(); // Pantalla de salida

protected:
    clsAudio audio; // Manejo de audio
    clsError error; // Manejo de errores
    clsEvent event; // Manejo de eventos
    clsMode mode; // Manejo del modo grafico
    clsMusic music; // Manejo de la musica
    clsRandom random; // Manejo de eventos aleatorios
    clsScreen screen; // Manejo del monitor de video
    clsText text; // Manejo de textos
    clsBug bug; // Control del personaje principal
    clsBug enemie[36]; // Control de los enemigos
    clsPressableKey pressableKey[11]; // Manejo de las posibles teclas a presionar
    clsScene scene; // Manejo de la escena

private:
    void bringGameToLife(); // Animacion del juego
    void gameOver(); // Pantalla de juego terminado
    void initializeGame(); // Inicializador de juego
    void pause(); // Manejo de la pausa del juego
    void saveOnExit(); // Administrador del guardado del juego al salir
    bool setKeyPressed(Uint16, bool); // Establece la/s teclas presionadas
};

#endif // CLSENGINE_H
