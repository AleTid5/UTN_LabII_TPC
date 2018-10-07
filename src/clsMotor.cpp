#include "clsMotor.h"

int clsMotor::init()
{
    error.set(0);
    error.set(mode.init(1366, 750, 0)); //Inicio el modo grafico (Quito 18px de altura por la bara del titulo)

    mode.crashPrevent();

    error.set(screen.init(mode.getScrWidth(),   //Inicio la pantalla
                          mode.getScrHeight(),
                          mode.getScrDepth(),
                          ENABLED,
                          NOTHING));

    screen.setTitle("Killer Bug");

    error.set(scene.init("IMAGES/landscapes/wallpaper.jpg"));

    error.set(bug.init("IMAGES/bugs/killerbug.png", 50, 100));

    error.set(mucus.init("IMAGES/bugs/mucus.png", 50, 100));

    error.set(audio.init());

    error.set(music.loadMusic("SOUNDS/bugs/spit.mp3"));

    return error.get();
}
int clsMotor::run()
{
    error.set(0);
    screen.clean(BLACK);              //Limpio la pantalla
    scene.paste(screen.getPtr());
    bug.paste(screen.getPtr());
    screen.refresh();              //Refresco la pantalla

    for(;;) { // Ciclo del programa
        while (event.wasEvent()) { // Verifico si hay evento
            while (event.getEventType() == KEY_PRESSED) { // Verifico si hay evento de teclado
                this->keyCommand(event.getKey()); // Administro la tecla
                event.wasEvent();
            }
        }
    }
    music.stopMusic();
    music.closeMusic();
    audio.closeAudio();

    return error.get();
}
int clsMotor::keyCommand(Uint16 key)
{
    error.set(0);

    if (key == KEY_ESCAPE) throw 0;

    if (key == KEY_w) bug.move(UP, &scene, &screen);
    if (key == KEY_s) bug.move(DOWN, &scene, &screen);
    if (key == KEY_a) bug.move(LEFT, &scene, &screen);
    if (key == KEY_d) bug.move(RIGHT, &scene, &screen);
    if (key == KEY_SPACE) bug.fire(&mucus, &scene, &screen, &event, &music);

    return error.get();
}
