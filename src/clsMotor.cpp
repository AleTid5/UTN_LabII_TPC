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
        "IMAGES/bugs/killerbug7.png"};

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

    enemie[35].init("IMAGES/enemies/boss.png", 1200, 100);
    enemie[35].energy = new clsEnergy(500);
    enemie[35].mucus = new clsMucus();

    error.set(audio.init());
    error.set(music.loadMusic("SOUNDS/bugs/spit.mp3"));
    error.set(scene.initText());
    random.init();
}
void clsMotor::run()
{
    error.set(0);
    screen.clean(BLACK); // Limpio la pantalla
    scene.loadWallpaper(&screen, &event);
    scene.showMenu(&screen);
    scene.startTimer();
    bug.energy->setEvolution(0);

    while (bug.energy->getLife() > 0) { // Ciclo del programa
        scene.move(&screen);
        bug.setI(bug.getEvolutionLevel());
        bug.paste(screen.getPtr());

        for (int i = 0; i < 35; i++) {
            enemie[i].fly(&screen, &random);
            enemie[i].enemyFire(&bug, &scene, &screen, &music);
        }

        if (bug.getEvolutionLevel() == 7)
            enemie[35].fly(&screen);

        bug.energy->updateStatusBar(&screen, &scene, bug.getEnemiesKilled());
        screen.refresh();

        if (event.wasEvent()) {
            while (event.getEventType() == KEY_PRESSED && isKeyPressable(event.getKey())) {
                this->keyCommand(event.getKey()); // Administro la tecla

                for (int i = 0; i < 35; i++) {
                    enemie[i].fly(&screen, &random);
                    enemie[i].enemyFire(&bug, &scene, &screen, &music);
                }

                screen.refresh();
                event.wasEvent();
            }
        }
    }

    //Perdió
    init();
    run();
}

void clsMotor::keyCommand(Uint16 key)
{
    if (key == KEY_ESCAPE)
        throw 0;

    if (key == KEY_w || key == KEY_UP)
        bug.move(UP, &scene, &screen);
    if (key == KEY_s || key == KEY_DOWN)
        bug.move(DOWN, &scene, &screen);
    if (key == KEY_a || key == KEY_LEFT)
        bug.move(LEFT, &scene, &screen);
    if (key == KEY_d || key == KEY_RIGHT)
        bug.move(RIGHT, &scene, &screen);
    if (key == KEY_SPACE)
        bug.fire(enemie, &scene, &screen, &event, &music, &random);

    if (key == KEY_f)
        bug.energy->setLife(bug.energy->getLife() - 1);

    if (key == KEY_g)
        bug.energy->setLife(100);

    error.set(error.get());
}

void clsMotor::stopRun()
{
    music.stopMusic();
    music.closeMusic();
    audio.closeAudio();
}

bool clsMotor::isKeyPressable(Uint16 key)
{
    return key == KEY_a || key == KEY_s || key == KEY_d || key == KEY_w ||
           key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT ||
           key == KEY_f || key == KEY_g || key == KEY_SPACE || key == KEY_ESCAPE;
}
