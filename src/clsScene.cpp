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

int clsScene::init(const char path[100][100], unsigned int countOfImages, unsigned int posX, unsigned int posY)
{
    setItems(countOfImages);
    for (unsigned int i = 0; i < countOfImages; i++) {
        setI(i);
        error.set(load(path[i]));
        setName(path[i]);
        setX(posX);
        setY(posY);
        setI(i);
    }

    return error.get();
}

void clsScene::loadWallpaper(clsScreen* screen, clsEvent* event)
{
    const char pathes[100][100] = {"IMAGES/landscapes/wallpaper.jpg", "IMAGES/landscapes/landscape.jpg"};

    error.set(this->init(pathes, 2, 0, 0));
    this->setI(0);
    this->paste(screen->getPtr());
    screen->refresh();
    clsScene killerTextImage;
    error.set(killerTextImage.init("IMAGES/landscapes/killer-text.jpg"));
    clsTimer timer;
    killerTextImage.setOpacity(1);
    killerTextImage.setX(screen->getWidth() / 2 - killerTextImage.getWidth() / 2);
    killerTextImage.setY(screen->getHeight() / 2 - killerTextImage.getHeight() / 2);

    while (killerTextImage.getOpacity() <= 45) {
        event->wasEvent();
        if (event->getKey() == KEY_ESCAPE) throw 0;
        killerTextImage.setOpacity(killerTextImage.getOpacity() + 1);
        killerTextImage.paste(screen->getPtr());
        screen->refresh();
        timer.wait(50);
    }

    int posY = killerTextImage.getY() + killerTextImage.getHeight() + 50; // 50px debajo
    clsScene txtAux = killerTextImage; // Me guardo el primer texto.
    txtAux.setOpacity(255);

    killerTextImage.init("IMAGES/landscapes/start-text.jpg", 0, posY);
    killerTextImage.setOpacity(0);
    killerTextImage.setX(screen->getWidth() / 2 - killerTextImage.getWidth() / 2);
    bool ascendant = true;
    while (event->getKey() != KEY_ENTER) {
        event->wasEvent();

        if (event->getKey() == KEY_ESCAPE) throw 0;

        killerTextImage.setOpacity(killerTextImage.getOpacity() + (ascendant ? 5 : - 5));

        if (killerTextImage.getOpacity() == 255 || killerTextImage.getOpacity() == 0)
            ascendant = ! ascendant;

        this->paste(screen->getPtr());
        txtAux.paste(screen->getPtr());
        killerTextImage.paste(screen->getPtr());
        screen->refresh();
    }

    this->setI(1);
    this->paste(screen->getPtr());
    screen->refresh();
}

void clsScene::move(clsScreen* screen)
{
    if (-1 * this->getX() == this->getWidth() - 1370) this->setX(-4);
    this->setX(this->getX() - 4);
    this->paste(screen->getPtr());
}



