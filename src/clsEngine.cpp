//#############################################################################
// ARCHIVO             : clsEngine.cpp
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
#include "clsEngine.h"

//=============================================================================
// METODO    : void init()
// ACCION    : Inicio del motor
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::init()
{
    error.set(mode.init(1366, 750, 0)); //Inicio el modo grafico (Quito 18px de altura por la bara del titulo)
    error.set(mode.setEnvironment("SDL_VIDEO_WINDOW_POS=center"));

    mode.crashPrevent();

    error.set(screen.init(mode.getScrWidth(),   //Inicio la pantalla
                          mode.getScrHeight(),
                          mode.getScrDepth(),
                          ENABLED,
                          NOTHING));

    screen.setTitle("Killer Bug");

    const char bugs[100][100] = {
            "IMAGES/bugs/killerbug0.png",
            "IMAGES/bugs/killerbug1.png",
            "IMAGES/bugs/killerbug2.png",
            "IMAGES/bugs/killerbug3.png",
            "IMAGES/bugs/killerbug4.png",
            "IMAGES/bugs/killerbug5.png",
            "IMAGES/bugs/killerbug6.png",
            "IMAGES/bugs/killerbug7.png"
    };

    error.set(bug.init(bugs, 8, 50, 100));
    bug.energy = new clsEnergy(100);
    bug.mucus = new clsMucus();

    char enemiePath[26];
    strcpy(enemiePath, "IMAGES/enemies/enemieX.png");
    int bugsInBlock = 1;
    int posX = 900;
    int posY = 100;
    for (int i = 0; i < 35; i++) {
        bugsInBlock = ! (bool) (i % 3) ? 1 : bugsInBlock + 1;
        enemiePath[21] = (! (i % 4) ? '4' : ! (i % 3) ? '3' : ! (i % 2) ? '2' : '1');
        if (bugsInBlock == 1) {
            posX = 1200 + (i * 100);
            posY = 100;
        } else {
            posY += 200;
        }
        enemie[i].init(enemiePath, posX, posY);
        enemie[i].energy = new clsEnergy(25);
        enemie[i].mucus = new clsMucus(true);
        enemie[i].mucus->setX(posX);
        enemie[i].mucus->setY(posY + 125);
    }

    enemie[35].init("IMAGES/enemies/boss.png", 1000, 100);
    enemie[35].energy = new clsEnergy(500);
    enemie[35].mucus = new clsMucus(true);

    pressableKey[0] = KEY_w;
    pressableKey[1] = KEY_UP;
    pressableKey[2] = KEY_s;
    pressableKey[3] = KEY_DOWN;
    pressableKey[4] = KEY_d;
    pressableKey[5] = KEY_RIGHT;
    pressableKey[6] = KEY_a;
    pressableKey[7] = KEY_LEFT;
    pressableKey[8] = KEY_SPACE;
    pressableKey[9] = KEY_ESCAPE;
    pressableKey[10] = KEY_p;

    error.set(audio.init());
    error.set(music.loadMusic("SOUNDS/bugs/spit.mp3"));
    scene.initText();
    random.init();
}

//=============================================================================
// METODO    : void run(bool playAgain)
// ACCION    : Vida del motor
// PARAMETROS: bool playAgain -> Determina si es una partida nueva.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::run(bool playAgain)
{
    screen.clean(BLACK); // Limpio la pantalla

    if (! playAgain)
        scene.loadWallpaper(&screen, &event);

    scene.showMenu(&screen);
    this->initializeGame();
    clsTimer timer;
    timer.start();

    const int FRAMES_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
    int nextTicks = timer.getTicks();
    int sleepTime = 0;

    while (bug.energy->getLife() > 0 && enemie[35].energy->getLife() > 0) { // Ciclo del programa
        bringGameToLife();
        screen.refresh();
        event.wasEvent();

        this->setKeyPressed(event.getKey(), event.getEventType() == KEY_PRESSED);
        this->keyCommand(); // Administro la tecla

        nextTicks += SKIP_TICKS;
        sleepTime = nextTicks - timer.getTicks();
        if (sleepTime >= 0) {
            timer.wait(sleepTime);
        }
    }

    this->gameOver();
    this->init();
    this->run(true);
}

//=============================================================================
// METODO    : void keyCommand()
// ACCION    : Manejo de las teclas presionadas
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::keyCommand()
{
    if (pressableKey[9].isKeyPressed()) {
        this->saveOnExit();
        this->init();
        this->run(true);
        throw 0;
    }

    if (pressableKey[0].isKeyPressed() || pressableKey[1].isKeyPressed())
        bug.move(UP, &scene, &screen);
    if (pressableKey[2].isKeyPressed() || pressableKey[3].isKeyPressed())
        bug.move(DOWN, &scene, &screen);
    if (pressableKey[4].isKeyPressed() || pressableKey[5].isKeyPressed())
        bug.move(RIGHT, &scene, &screen);
    if (pressableKey[6].isKeyPressed() || pressableKey[7].isKeyPressed())
        bug.move(LEFT, &scene, &screen);
    if (pressableKey[8].isKeyPressed() && ! bug.mucus->isAttacking())
        bug.fire(enemie, &scene, &screen, &music);
    if (pressableKey[10].isKeyPressed())
        this->pause();

    error.set(error.get());
}

//=============================================================================
// METODO    : void stopRun()
// ACCION    : Manejo al dejar de jugar
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::stopRun()
{
    music.stopMusic();
    music.closeMusic();
    audio.closeAudio();
}

//=============================================================================
// METODO    : void initializeGame()
// ACCION    : Inicializador de juego
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::initializeGame()
{
    if (5 == scene.getOptionSelected()) {
        clsScene help;
        help.init("IMAGES/landscapes/howtoplay.png", 0, 0);
        help.paste(screen.getPtr());
        screen.refresh();
        scene.timer.waitForKey(KEY_ENTER);
        this->run(true);
    }

    if (3 == scene.getOptionSelected()) {
        clsGameData gameData;
        clsScene points;
        points.init("IMAGES/landscapes/top-10.jpg", 0, 0);
        points.paste(screen.getPtr());
        int posY = 250;
        unsigned int position = 0;
        gameData.read("Game_Data/points.b", "rb", position);
        for (int i = 0; gameData.wasRead && i < 10; i++) {
            position++;
            int points = ((gameData.enemiesKilled + 1) * 1300) + (gameData.enemiesKilled == 0 ? gameData.time : gameData.time * -1);
            scene.writeText(&screen, gameData.playierName, 75, posY);
            scene.writeText(&screen, gameData.enemiesKilled, 500, posY);
            scene.writeText(&screen, gameData.time, 850, posY);
            scene.writeText(&screen,points, 1150, posY);
            posY += 49;
            gameData.read("Game_Data/points.b", "rb", position);
        }

        screen.refresh();
        scene.timer.waitForKey(KEY_ENTER);

        this->run(true);
    }

    event.setEventType(KEY_FREE);
    int enemiesKilled = 0;
    int energyEvolution = 0;
    int energyLife = 100;
    for (int i = 0; i < 11; i++)
        pressableKey[i] > false;

    scene.startTimer();

    if (2 == scene.getOptionSelected()) {
        clsGameData game;
        game.read("Game_Data/resume.b", "rb");

        if (! game.wasRead) {
            clsScene continueError;
            continueError.init("IMAGES/landscapes/404.png", 0, 0);
            continueError.paste(screen.getPtr());
            screen.refresh();
            scene.timer.waitForKey(KEY_ENTER);
            this->run(true);
        }

        enemiesKilled = game.enemiesKilled;
        energyEvolution = game.evolutionEnergy;
        energyLife = game.life;
        scene.setTime(game.time);
        enemie[35].energy->setLife(game.bossLife);
        for (int i = 0; i < 36; i++) {
            enemie[i].setX(game.enemies[i][0]);
            enemie[i].setY(game.enemies[i][1]);
        }
        game.removeFile("Game_Data/resume.b"); // Elimino el archivo para que no retome si pierde o gana
    }

    bug.setEnemiesKilled(enemiesKilled);
    bug.setEvolutionLevel(bug.getEnemiesKilled() / 5);
    bug.setSpeed((bug.getEvolutionLevel() + 1) * 4);
    bug.mucus->setFireSpeed(15 + (bug.getEvolutionLevel() * 2));
    bug.energy->setEvolution(energyEvolution);
    bug.energy->setLife(energyLife);

    for (int i = 0; i < 35; i++)
        enemie[i].mucus->setFireSpeed((bug.getEvolutionLevel() + 1) * 5);

    enemie[35].mucus->setFireSpeed(30);
    enemie[35].energy->setDamage(50);
}

//=============================================================================
// METODO    : bool setKeyPressed(Uint16 key, bool status)
// ACCION    : Establece la/s teclas presionadas
// PARAMETROS: Uint16 key -> Tecla presionada.
//             bool status -> Estado de la tecla presionada.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
bool clsEngine::setKeyPressed(Uint16 key, bool status)
{
    for (int i = 0; i < 11; i++)
        if (this->pressableKey[i].getKey() == (int) key) {
            pressableKey[i] > status;
            return true;
        }

    return false;
}

//=============================================================================
// METODO    : void bringGameToLife()
// ACCION    : Animacion del juego
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::bringGameToLife()
{
    scene.move(&screen);

    bug.setI(bug.getEvolutionLevel());
    bug.paste(screen.getPtr());

    if (bug.getEvolutionLevel() == 7) {
        enemie[35].fly(&screen, &random, 1050, 500);
        enemie[35].enemyFire(&bug, &screen);
    } else {
        for (int i = 0; i < 35; i++) {
            enemie[i].fly(&screen, &random);
            enemie[i].enemyFire(&bug, &screen);
        }
    }

    bug.energy->updateStatusBar(&screen, &scene, bug.getEnemiesKilled(), enemie[35].energy->getLife());

    if (bug.mucus->isAttacking())
        bug.fire(enemie, &scene, &screen, &music);
}

//=============================================================================
// METODO    : void saveOnExit()
// ACCION    : Administrador del guardado del juego al salir
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::saveOnExit()
{
    clsGameData game;
    game.enemiesKilled = bug.getEnemiesKilled();
    game.life = bug.energy->getLife();
    game.evolutionEnergy = bug.energy->getEvolution();
    game.time = scene.getTime();
    game.bossLife = enemie[35].energy->getLife();
    for (int i = 0; i < 36; i++) {
        game.enemies[i][0] = enemie[i].getX();
        game.enemies[i][1] = enemie[i].getY();
    }
    game.save("Game_Data/resume.b", "wb+");
}

//=============================================================================
// METODO    : void gameOver()
// ACCION    : Pantalla de juego terminado
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::gameOver()
{
    int playiedTime = scene.timer.getPlayiedTime() / 1000;
    clsScene gameOver[3];
    const char* gameCompleted = bug.getEnemiesKilled() == 36 ? "IMAGES/landscapes/gameWon.png" : "IMAGES/landscapes/gameOver.png";
    gameOver[0].init(gameCompleted, 50, -50);
    gameOver[1].init("IMAGES/landscapes/start-text.png", 500, 600);
    gameOver[2].init("IMAGES/landscapes/points.png", 750, 95);

    bool ascendant = true;
    char name[5];
    for (int i = 0; i < 5; i++)
        name[i] = '\0';

    int i = 0;

    while (event.getKey() != KEY_ENTER || name[2] == '\0') {
        if (event.wasEvent()) {
            if (event.getEventType() == KEY_PRESSED && event.getKey() != KEY_BACKSPACE) {
                int letter = (int) event.getKey();
                if (i < 4 && ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122) || (letter >= 48 && letter <= 57))) {
                    name[i] = (char) letter;
                    i++;
                }
            } else if (event.getEventType() == KEY_PRESSED && event.getKey() == KEY_BACKSPACE) {
                if (i > 0) {
                    i--;
                    name[i] = (char) '\0';
                }
            }
        }

        gameOver[0].setY(gameOver[0].getY() + (ascendant ? 1 : - 1));

        if (gameOver[0].getY() == -50 || gameOver[0].getY() == 0)
            ascendant = ! ascendant;

        int points = ((bug.getEnemiesKilled() + 1) * 1300) + (bug.getEnemiesKilled() == 0 ? playiedTime : playiedTime * -1);

        scene.paste(screen.getPtr());
        gameOver[0].paste(screen.getPtr());
        gameOver[1].paste(screen.getPtr());
        gameOver[2].paste(screen.getPtr());
        scene.writeText(&screen, playiedTime, 885, 130);
        scene.writeText(&screen, bug.getEnemiesKilled(), 885, 250);
        scene.writeText(&screen, points, 875, 370);
        if (name[0] != '\0')
            scene.writeText(&screen, name, 875, 450);
        screen.refresh();
    }

    clsGameData* game = new clsGameData();
    game->enemiesKilled = bug.getEnemiesKilled();
    game->time = playiedTime;
    strcpy(game->playierName, name);
    game->arrangedSave("Game_Data/points.b", "ab+");
    game->removeFile("Game_Data/resume.b");
}

//=============================================================================
// METODO    : void pause()
// ACCION    : Manejo de la pausa del juego
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::pause()
{
    for (int i = 0; i < 11; i++) pressableKey[i] > false;
    scene.timer.pause(true);
    clsScene* goodBye = new clsScene();
    goodBye->init("IMAGES/landscapes/paused.png", 0, 0);
    goodBye->paste(screen.getPtr());
    screen.refresh();

    event.wasEvent();
    while (event.getKey() != KEY_ENTER && event.getKey() != KEY_ESCAPE) event.wasEvent();
    scene.timer.pause(false);

    if (event.getKey() == KEY_ESCAPE) {
        this->saveOnExit();
        this->init();
        this->run(true);
    }
}

//=============================================================================
// METODO    : void comeBackSoon()
// ACCION    : Pantalla de salida
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//-----------------------------------------------------------------------------
void clsEngine::comeBackSoon()
{
    screen.clean(BLACK);
    clsScene* goodBye = new clsScene();
    const char* comeBack = bug.getEnemiesKilled() == 36 ? "IMAGES/landscapes/ByeWon.png" : "IMAGES/landscapes/ByeLose.png";
    goodBye->init(comeBack, 0, 0);
    goodBye->paste(screen.getPtr());
    screen.refresh();
    scene.timer.waitForKey(KEY_ESCAPE);
}