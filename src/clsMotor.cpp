#include "clsMotor.h"

void clsMotor::init()
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
        enemie[i].mucus = new clsMucus();
        enemie[i].mucus->setX(posX);
        enemie[i].mucus->setY(posY + 125);
    }

    enemie[35].init("IMAGES/enemies/boss.png", 1000, 100);
    enemie[35].energy = new clsEnergy(500);
    enemie[35].mucus = new clsMucus();

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

    error.set(audio.init());
    error.set(music.loadMusic("SOUNDS/bugs/spit.mp3"));
    error.set(scene.initText());
    random.init();
}
void clsMotor::run(bool playAgain)
{
    screen.clean(BLACK); // Limpio la pantalla
    if (! playAgain)
        scene.loadWallpaper(&screen, &event);
    scene.showMenu(&screen);
    this->initializeGame();

    clsTimer timer;
    timer.start();

    const int FRAMES_PER_SECOND = 30;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

    int nextTicks = timer.getTicks();

    int sleepTime = 0;

    while (bug.energy->getLife() > 0 && enemie[35].energy->getLife() > 0) { // Ciclo del programa

        bringGameToLife(&screen, &scene, &music, &random, &bug, enemie);

        if (bug.mucus->isAttacking())
            bug.fire(enemie, &scene, &screen, &event, &music, &random);

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

void clsMotor::keyCommand()
{
    if (pressableKey[9].isKeyPressed()) {
        this->saveOnExit();
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
    if (pressableKey[8].isKeyPressed())
        bug.fire(enemie, &scene, &screen, &event, &music, &random);

    error.set(error.get());
}

void clsMotor::stopRun()
{
    music.stopMusic();
    music.closeMusic();
    audio.closeAudio();
}

void clsMotor::initializeGame()
{
    event.setEventType(KEY_FREE);
    int enemiesKilled = 0;
    int energyEvolution = 0;
    int energyLife = 100;
    for (int i = 0; i < 10; i++)
        pressableKey[i] > false;

    scene.startTimer();

    if (2 == scene.getOptionSelected()) {
        clsGame game;
        game.read("Game_Data/resume.b", "rb");
        enemiesKilled = game.enemiesKilled;
        energyEvolution = game.evolutionEnergy;
        energyLife = game.life;
        scene.setTime(game.time);
        for (int i = 0; i < 36; i++) {
            enemie[i].setX(game.enemies[i][0]);
            enemie[i].setY(game.enemies[i][1]);
        }
        game.removeFile("Game_Data/resume.b"); // Elimino el archivo para que no retome si pierde o gana
    }

    bug.setEnemiesKilled(enemiesKilled);
    bug.setEvolutionLevel(bug.getEnemiesKilled() / 5);
    bug.setSpeed((bug.getEvolutionLevel() + 1) * 10);
    bug.energy->setEvolution(energyEvolution);
    bug.energy->setLife(energyLife);

    for (int i = 0; i < 35; i++)
        enemie[i].mucus->setFireSpeed((bug.getEvolutionLevel() + 1) * 5);

    enemie[35].mucus->setFireSpeed(30);
    enemie[35].energy->setDamage(50);
}

bool clsMotor::setKeyPressed(Uint16 key, bool status)
{
    for (int i = 0; i < 10; i++)
        if (this->pressableKey[i].getKey() == (int) key) {
            pressableKey[i] > status;
            return true;
        }

    return false;
}

void clsMotor::bringGameToLife(clsScreen* screen, clsScene* scene, clsMusic* music, clsRandom* random, clsBug* bug, clsBug* enemie)
{
    scene->move(screen);

    bug->setI(bug->getEvolutionLevel());
    bug->paste(screen->getPtr());

    if (bug->getEvolutionLevel() == 7) {
        enemie[35].fly(screen, random);
        enemie[35].enemyFire(bug, scene, screen, music);
    } else {
        for (int i = 0; i < 35; i++) {
            enemie[i].fly(screen, random);
            enemie[i].enemyFire(bug, scene, screen, music);
        }
    }

    bug->energy->updateStatusBar(screen, scene, bug->getEnemiesKilled());
}

void clsMotor::saveOnExit()
{
    clsGame game;
    game.enemiesKilled = bug.getEnemiesKilled();
    game.life = bug.energy->getLife();
    game.evolutionEnergy = bug.energy->getEvolution();
    game.time = scene.getTime();
    for (int i = 0; i < 36; i++) {
        game.enemies[i][0] = enemie[i].getX();
        game.enemies[i][1] = enemie[i].getY();
    }
    game.save("Game_Data/resume.b", "wb+");
}

void clsMotor::gameOver() {
    int playiedTime = scene.timer.getPlayiedTime();
    clsScene gameOver[3];
    gameOver[0].init("IMAGES/landscapes/gameOver.png", 50, -50);
    gameOver[1].init("IMAGES/landscapes/start-text.png", 500, 600);
    gameOver[2].init("IMAGES/landscapes/points.png", 750, 95);

    bool ascendant = true;
    while (event.getKey() != KEY_ENTER) {
        event.wasEvent();

        gameOver[0].setY(gameOver[0].getY() + (ascendant ? 1 : - 1));

        if (gameOver[0].getY() == -50 || gameOver[0].getY() == 0)
            ascendant = ! ascendant;

        scene.paste(screen.getPtr());
        gameOver[0].paste(screen.getPtr());
        gameOver[1].paste(screen.getPtr());
        gameOver[2].paste(screen.getPtr());
        scene.writeText(&screen, playiedTime / 1000, 885, 130);
        scene.writeText(&screen, bug.getEnemiesKilled(), 885, 250);
        screen.refresh();
    }
}
