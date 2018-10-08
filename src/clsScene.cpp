#include "clsScene.h"

int clsScene::init(const char* path, unsigned int posX, unsigned int posY)
{
    setItems(1);  // Cantidad de imagenes 1.
    setI(0);      // Indice del vector de imagenes.

    // Cargar la imagen.
    error.set(load(path));

    setName(path);
    setX(posX);
    setY(posY);
    setI(0);

    return error.get();
}

void clsScene::loadWallpaper(clsScreen* screen)
{
    error.set(this->init("IMAGES/landscapes/wallpaper.jpg"));
    this->paste(screen->getPtr());
    screen->refresh();
    clsScene killerText;
    error.set(killerText.init("IMAGES/landscapes/text-killerbug.png"));
    killerText.paste(screen->getPtr());
    screen->refresh();
}



