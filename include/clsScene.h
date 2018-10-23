#ifndef CLSSCENE_H
#define CLSSCENE_H
#include <clsSprite.h>
#include <clsText.h>
#include <clsTimer.h>

class clsScene : public clsSprite
{
public:
    int init(const char*, unsigned int posX = 0, unsigned int posY = 0);
    int init(const char path[100][100], unsigned int, unsigned int posX = 0, unsigned int posY = 0);
    int initText();
    void addKill(clsScreen*, unsigned int, unsigned int, unsigned int);
    void loadWallpaper(clsScreen*, clsEvent*);
    void move(clsScreen*);
    void startTimer();
    void showTimer(clsScreen*);
    void showMenu(clsScreen*);

protected:
    void inherit() {};

private:
    clsTimer timer;
    clsText text;
    void dispatchOption(clsScene*, clsScreen*);
};

#endif // CLSSCENE_H
