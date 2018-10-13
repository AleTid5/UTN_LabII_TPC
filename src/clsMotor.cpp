#include "clsMotor.h"

void clsMotor::init()
{
    error.set(0);
    error.set(mode.init(1366, 750, 0)); //Inicio el modo grafico (Quito 18px de altura por la bara del titulo)
    error.set(mode.setEnvironment("SDL_VIDEO_WINDOW_POS=center"));

    mode.crashPrevent();

    error.set(screen.init(mode.getScrWidth(),   //Inicio la pantalla
                          mode.getScrHeight(),
                          mode.getScrDepth(),
                          ENABLED,
                          NOTHING));

    screen.setTitle("Killer Bug");

    //error.set(bug.init("IMAGES/bugs/killerbug.png", 50, 100));

    const char pathes[100][100] = {"IMAGES/bugs/killerbug.png", "IMAGES/bugs/killerbug2.png", "IMAGES/bugs/killerbug3.png"};

    error.set(bug.init(pathes, 3, 50, 100));

    error.set(mucus.init("IMAGES/bugs/mucus.png", 50, 100));

    error.set(audio.init());

    error.set(music.loadMusic("SOUNDS/bugs/spit.mp3"));
}
void clsMotor::run()
{
    error.set(0);
    screen.clean(BLACK); // Limpio la pantalla
    scene.loadWallpaper(&screen, &event);

    for(;;) { // Ciclo del programa
        scene.move(&screen);
        bug.fly(&screen);

        if (event.wasEvent()) { // Verifico si hay evento
            // Verifico si hay evento de teclado
            while (event.getEventType() == KEY_PRESSED) {
                this->keyCommand(event.getKey()); // Administro la tecla
                event.wasEvent();
            }
        }
    }

    music.stopMusic();
    music.closeMusic();
    audio.closeAudio();

    error.set(error.get());
}

void clsMotor::keyCommand(Uint16 key)
{
    error.set(0);

    if (key == KEY_ESCAPE) throw 0;

    if (key == KEY_w || key == KEY_UP) bug.move(UP, &scene, &screen);
    if (key == KEY_s || key == KEY_DOWN) bug.move(DOWN, &scene, &screen);
    if (key == KEY_a || key == KEY_LEFT) bug.move(LEFT, &scene, &screen);
    if (key == KEY_d || key == KEY_RIGHT) bug.move(RIGHT, &scene, &screen);
    if (key == KEY_SPACE) bug.fire(&mucus, &scene, &screen, &event, &music);

    error.set(error.get());
}
