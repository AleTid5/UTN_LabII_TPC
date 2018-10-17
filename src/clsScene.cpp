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

int clsScene::initText()
{
    error.set(this->text.init());

    error.set(this->text.loadFont("FONTS/FreeMono.ttf", 25));

    return 0;
}

void clsScene::loadWallpaper(clsScreen* screen, clsEvent* event)
{
    const char pathes[100][100] = {
        "IMAGES/landscapes/wallpaper.jpg",
        "IMAGES/landscapes/landscape.jpg"};

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
    this->setI(1);
    if (-1 * this->getX() == this->getWidth() - 1370) this->setX(-4);

    this->setX(this->getX() - 4);
    this->paste(screen->getPtr());

    clsScene statusBar;
    statusBar.init("IMAGES/landscapes/status-bar.png", 0, 0);
    statusBar.paste(screen->getPtr());

    this->showTimer(screen);
}

void clsScene::startTimer()
{
    this->timer.start();
}

void clsScene::showTimer(clsScreen* screen)
{
    this->timer.update();
    string timeString = to_string(this->timer.getState() / 1000);
    const char *time = timeString.c_str();
    this->text.setFontColor(WHITE);
    this->text.write(time, screen->getWidth() / 2 - this->text.getWidth() / 2, 15, screen->getPtr());
}

void clsScene::showMenu(clsScreen* screen)
{
    const char pathes[100][100] = {
        "IMAGES/menu/startPost.png",
        "IMAGES/menu/startPostPlay.png",
        "IMAGES/menu/startPostContinue.png",
        "IMAGES/menu/startPostScore.png",
        "IMAGES/menu/startPostExit.png"
    };

    clsScene* menu = new clsScene;
    menu->error.set(menu->init(pathes, 5, 300, 100));
    menu->setI(0);
    menu->paste(screen->getPtr());
    screen->refresh();
    this->dispatchOption(menu, screen);

}

void clsScene::dispatchOption(clsScene* menu, clsScreen* screen)
{
    clsEvent* event = new clsEvent;

    while (event->getMouseButton() != MOUSE_LEFT_BUTTON || menu->getI() == 0) {
        Uint16 posX = event->getCursorX();
        Uint16 posY = event->getCursorY();

        menu->setI(0);

        if (posX >= 360 && posX <= 750 && posY >= 100 && posY <= 225)
            menu->setI(1);
        else if (posX >= 300 && posX <= 630 && posY >= 225 && posY <= 290)
            menu->setI(2);
        else if (posX >= 450 && posX <= 675 && posY >= 290 && posY <= 350)
            menu->setI(3);
        else if (posX >= 415 && posX <= 675 && posY >= 410 && posY <= 475)
            menu->setI(4);

        this->paste(screen->getPtr());
        menu->paste(screen->getPtr());
        screen->refresh();
        event->wasEvent();
    }

    if (menu->getI() == 4) throw 0;

    if (menu->getI() == 1) {}// JUGAR
}



